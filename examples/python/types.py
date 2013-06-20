#!/usr/bin/python

#----------------------------------------------------------------------
# Be sure to add the python path that points to the LLDB shared library.
#
# # To use this in the embedded python interpreter using "lldb" just
# import it with the full path using the "command script import" 
# command
#   (lldb) command script import /path/to/cmdtemplate.py
#----------------------------------------------------------------------

import commands
import platform
import os
import sys

try: 
    # Just try for LLDB in case PYTHONPATH is already correctly setup
    import lldb
except ImportError:
    lldb_python_dirs = list()
    # lldb is not in the PYTHONPATH, try some defaults for the current platform
    platform_system = platform.system()
    if platform_system == 'Darwin':
        # On Darwin, try the currently selected Xcode directory
        xcode_dir = commands.getoutput("xcode-select --print-path")
        if xcode_dir:
            lldb_python_dirs.append(os.path.realpath(xcode_dir + '/../SharedFrameworks/LLDB.framework/Resources/Python'))
            lldb_python_dirs.append(xcode_dir + '/Library/PrivateFrameworks/LLDB.framework/Resources/Python')
        lldb_python_dirs.append('/System/Library/PrivateFrameworks/LLDB.framework/Resources/Python')
    success = False
    for lldb_python_dir in lldb_python_dirs:
        if os.path.exists(lldb_python_dir):
            if not (sys.path.__contains__(lldb_python_dir)):
                sys.path.append(lldb_python_dir)
                try: 
                    import lldb
                except ImportError:
                    pass
                else:
                    print 'imported lldb from: "%s"' % (lldb_python_dir)
                    success = True
                    break
    if not success:
        print "error: couldn't locate the 'lldb' module, please set PYTHONPATH correctly"
        sys.exit(1)

import commands
import optparse
import shlex
import time

def create_types_options():
    usage = "usage: %prog [options]"
    description='''This command will help you verify that types in your program
are packed efficiently by showing all types and their sizes and showing the 
padding bytes that waste space.
'''
    parser = optparse.OptionParser(description=description, prog='framestats',usage=usage)
    parser.add_option('-a', '--arch', type='string', dest='arch', help='The architecture to use when creating the debug target.', default=None)
    parser.add_option('-p', '--platform', type='string', metavar='platform', dest='platform', help='specify one platform by name')
    parser.add_option('-m', '--module', action='append', type='string', metavar='MODULE', dest='modules', help='Specify one or more modules which will be used to verify the types.', default=[])
    parser.add_option('-t', '--type', action='append', type='string', metavar='TYPENAME', dest='typenames', help='Specify one or more type names which should be verified. If no type names are specified, all class and struct types will be verified.', default=[])
    parser.add_option('-d', '--debug', action='store_true', dest='debug', help='Pause 10 seconds to wait for a debugger to attach.', default=False)
    parser.add_option('-v', '--verbose', action='store_true', dest='verbose', default=False)
    return parser

def verify_type (target, type):
    print type
    typename = type.GetName()
    # print 'type: %s' % (typename)
    (end_offset, padding) = verify_type_recursive (target, type, None, 0, 0, 0)
    byte_size = type.GetByteSize()
    # if end_offset < byte_size:
    #     last_member_padding = byte_size - end_offset
    #     print '%+4u <%u> padding' % (end_offset, last_member_padding)
    #     padding += last_member_padding
    print 'Total byte size: %u' % (byte_size)
    print 'Total pad bytes: %u' % (padding)
    if padding > 0:
        print 'Padding percentage: %2.2f %%' % ((float(padding) / float(byte_size)) * 100.0)
    print

def verify_type_recursive (target, type, member_name, depth, base_offset, padding):
    prev_end_offset = base_offset
    typename = type.GetName()
    byte_size = type.GetByteSize()
    if member_name and member_name != typename:
        print '%+4u <%3u> %s%s %s;' % (base_offset, type.GetByteSize(), '    ' * depth, typename, member_name)
    else:
        print '%+4u <%3u> %s%s' % (base_offset, type.GetByteSize(), '    ' * depth, typename)
    
    members = type.members
    if members:
        for member_idx, member in enumerate(members):
            member_type = member.GetType()
            member_canonical_type = member_type.GetCanonicalType()
            member_type_class = member_canonical_type.GetTypeClass()
            member_name = member.GetName()
            member_offset = member.GetOffsetInBytes()
            member_total_offset = member_offset + base_offset
            member_byte_size = member_type.GetByteSize()
            is_class_or_struct = False
            if member_type_class == lldb.eTypeClassStruct or member_type_class == lldb.eTypeClassClass:
                is_class_or_struct = True
            if member_idx == 0 and member_offset == target.GetAddressByteSize() and type.IsPolymorphicClass():
                ptr_size = target.GetAddressByteSize()
                print '%+4u <%3u> %s__vtbl_ptr_type * _vptr;' % (prev_end_offset, ptr_size, '    ' * (depth + 1))
                prev_end_offset = ptr_size
            else:
                if prev_end_offset < member_total_offset:
                    member_padding = member_total_offset - prev_end_offset
                    padding = padding + member_padding
                    print '%+4u <%3u> %s<PADDING>' % (prev_end_offset, member_padding, '    ' * (depth + 1))
        
            if is_class_or_struct:
                (prev_end_offset, padding) = verify_type_recursive (target, member_canonical_type, member_name, depth + 1, member_total_offset, padding)
            else:
                prev_end_offset = member_total_offset + member_byte_size
                if member.IsBitfield():
                    print '%+4u <%3u> %s%s:%u %s;' % (member_total_offset, member_byte_size, '    ' * (depth + 1), member_type.GetName(), member.GetBitfieldSizeInBits(), member_name)
                else:
                    print '%+4u <%3u> %s%s %s;' % (member_total_offset, member_byte_size, '    ' * (depth + 1), member_type.GetName(), member_name)
    
        if prev_end_offset < byte_size:
            last_member_padding = byte_size - prev_end_offset
            print '%+4u <%3u> %s<PADDING>' % (prev_end_offset, last_member_padding, '    ' * (depth + 1))
            padding += last_member_padding
    else:
        if type.IsPolymorphicClass():
            ptr_size = target.GetAddressByteSize()
            print '%+4u <%3u> %s__vtbl_ptr_type * _vptr;' % (prev_end_offset, ptr_size, '    ' * (depth + 1))
            prev_end_offset = ptr_size
        prev_end_offset = base_offset + type.GetByteSize()
    
    return (prev_end_offset, padding)
    
def types_command (debugger, command, result, dict):
    # Use the Shell Lexer to properly parse up command options just like a 
    # shell would
    command_args = shlex.split(command)
    verify_types(debugger, command_args)
    
def verify_types (debugger, command_args):

    parser = create_types_options()
    try:
        (options, args) = parser.parse_args(command_args)
    except:
        # if you don't handle exceptions, passing an incorrect argument to the OptionParser will cause LLDB to exit
        # (courtesy of OptParse dealing with argument errors by throwing SystemExit)
        result.SetStatus (lldb.eReturnStatusFailed)
        return "option parsing failed" # returning a string is the same as returning an error whose description is the string
    
    if options.debug:
        print 'Waiting for debugger to attach...'
        for i in range(10):
            time.sleep(1)
            print '.'
        
    for path in args:
    # in a command - the lldb.* convenience variables are not to be used
    # and their values (if any) are undefined
    # this is the best practice to access those objects from within a command
        error = lldb.SBError()
        target = debugger.CreateTarget (path,
                                        options.arch,
                                        options.platform,
                                        True,
                                        error)
        if error.Fail():
            print error.GetCString()
            continue
    
        modules = list()
        if len(options.modules) == 0:
            # Append just the main executable if nothing was specified
            module = target.modules[0]
            if module:
                modules.append(module)
        else:
            for module_name in options.modules:
                module = lldb.target.module[module_name]
                if module:
                    modules.append(module)
        
        if modules:
            for module in modules:
                print 'module: %s' % (module.file)
                if options.typenames:
                    for typename in options.typenames:
                        types = module.FindTypes(typename)
                        if types.GetSize():
                            print 'Found %u types matching "%s" in "%s"' % (len(types), typename, module.file)
                            for type in types:
                                verify_type (target, type)
                        else:
                            print 'error: no type matches "%s" in "%s"' % (typename, module.file)
                else:
                    types = module.GetTypes(lldb.eTypeClassClass | lldb.eTypeClassStruct)
                    print 'Found %u types in "%s"' % (len(types), module.file)
                    for type in types:
                        verify_type (target, type)
        else:
            print 'error: no modules'

if __name__ == '__main__':
    debugger = lldb.SBDebugger.Create()
    verify_types (debugger, sys.argv[1:])
elif getattr(lldb, 'debugger', None):
    lldb.debugger.HandleCommand('command script add -f types.types_command types')
    print '"types" command installed, use the "--help" option for detailed help'