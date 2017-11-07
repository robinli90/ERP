using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

/// This namespace includes all elements of the program.
namespace ProcessFF
{
    /// @brief Main execution class.
    /// It is the main class contains Main().
    /// @note This is the main class of the program. It creates
    /// MainDialog object.
    static class Program
    {
        [STAThread]
        /// Main function of the program. It configures dialog 
        /// and creates MainDialog object.
        /// @note static function
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new MainDialog());
        }
    }
}
