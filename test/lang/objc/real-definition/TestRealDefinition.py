"""Test that types defined in shared libraries work correctly."""

import os, time
import unittest2
import lldb
from lldbtest import *
import lldbutil

class TestRealDefinition(TestBase):

    mydir = TestBase.compute_mydir(__file__)

    @unittest2.skipUnless(sys.platform.startswith("darwin"), "requires Darwin")
    @dsym_test
    @expectedFailureDarwin("llvm.org/pr20272")
    def test_frame_var_after_stop_at_interface_with_dsym(self):
        """Test that we can find the implementation for an objective C type"""
        if self.getArchitecture() == 'i386':
            self.skipTest("requires modern objc runtime")
        self.buildDsym()
        self.stop_at_interface()

    @unittest2.skipUnless(sys.platform.startswith("darwin"), "requires Darwin")
    @dwarf_test
    @expectedFailureDarwin("llvm.org/pr20272")
    def test_frame_var_after_stop_at_interface_with_dwarf(self):
        """Test that we can find the implementation for an objective C type"""
        if self.getArchitecture() == 'i386':
            self.skipTest("requires modern objc runtime")
        self.buildDwarf()
        self.stop_at_interface()

    @unittest2.skipUnless(sys.platform.startswith("darwin"), "requires Darwin")
    @dsym_test
    @expectedFailureDarwin("llvm.org/pr20272")
    def test_frame_var_after_stop_at_implementation_with_dsym(self):
        """Test that we can find the implementation for an objective C type"""
        if self.getArchitecture() == 'i386':
            self.skipTest("requires modern objc runtime")
        self.buildDsym()
        self.stop_at_implementation()

    @unittest2.skipUnless(sys.platform.startswith("darwin"), "requires Darwin")
    @dwarf_test
    @expectedFailureDarwin("llvm.org/pr20272")
    def test_frame_var_after_stop_at_implementation_with_dwarf(self):
        """Test that we can find the implementation for an objective C type"""
        if self.getArchitecture() == 'i386':
            self.skipTest("requires modern objc runtime")
        self.buildDwarf()
        self.stop_at_implementation()

    def setUp(self):
        # Call super's setUp().
        TestBase.setUp(self)

    def common_setup(self):
        exe = os.path.join(os.getcwd(), "a.out")
        self.runCmd("file " + exe, CURRENT_EXECUTABLE_SET)

        # Break inside the foo function which takes a bar_ptr argument.
        line = line_number('main.m', '// Set breakpoint in main')
        lldbutil.run_break_set_by_file_and_line (self, "main.m", line, num_expected_locations=1, loc_exact=True)

    def stop_at_interface(self):
        """Test that we can find the implementation for an objective C type when we stop in the interface"""
        self.common_setup()

        line = line_number('Foo.m', '// Set breakpoint where Bar is an interface')
        lldbutil.run_break_set_by_file_and_line (self, 'Foo.m', line, num_expected_locations=1, loc_exact=True);

        self.runCmd("run", RUN_SUCCEEDED)

        # The stop reason of the thread should be breakpoint.
        self.expect("thread list", STOPPED_DUE_TO_BREAKPOINT,
            substrs = ['stopped',
                       'stop reason = breakpoint'])

        # Run and stop at Foo
        self.expect("breakpoint list -f", BREAKPOINT_HIT_ONCE,
            substrs = [' resolved, hit count = 1'])

        self.runCmd("continue", RUN_SUCCEEDED)

        # Run at stop at main
        self.expect("breakpoint list -f", BREAKPOINT_HIT_ONCE,
            substrs = [' resolved, hit count = 1'])
            
        # This should display correctly.
        self.expect("frame variable foo->_bar->_hidden_ivar", VARIABLES_DISPLAYED_CORRECTLY,
            substrs = ["(NSString *)", "foo->_bar->_hidden_ivar = 0x"])

    def stop_at_implementation(self):
        """Test that we can find the implementation for an objective C type when we stop in the implementation"""
        self.common_setup()

        line = line_number('Bar.m', '// Set breakpoint where Bar is an implementation')
        lldbutil.run_break_set_by_file_and_line (self, 'Bar.m', line, num_expected_locations=1, loc_exact=True)

        self.runCmd("run", RUN_SUCCEEDED)

        # The stop reason of the thread should be breakpoint.
        self.expect("thread list", STOPPED_DUE_TO_BREAKPOINT,
            substrs = ['stopped',
                       'stop reason = breakpoint'])

        # Run and stop at Foo
        self.expect("breakpoint list -f", BREAKPOINT_HIT_ONCE,
            substrs = [' resolved, hit count = 1'])

        self.runCmd("continue", RUN_SUCCEEDED)

        # Run at stop at main
        self.expect("breakpoint list -f", BREAKPOINT_HIT_ONCE,
            substrs = [' resolved, hit count = 1'])

        # This should display correctly.
        self.expect("frame variable foo->_bar->_hidden_ivar", VARIABLES_DISPLAYED_CORRECTLY,
            substrs = ["(NSString *)", "foo->_bar->_hidden_ivar = 0x"])

                       
if __name__ == '__main__':
    import atexit
    lldb.SBDebugger.Initialize()
    atexit.register(lambda: lldb.SBDebugger.Terminate())
    unittest2.main()
