using System.Collections.ObjectModel;
using System.Windows;
using WorkTimeTracking.Models;
using WorkTimeTracking.Views; // щоб бачити папку Views

namespace WorkTimeTracking
{
    public partial class MainWindow : Window
    {
        // ObservableCollection автоматично оновлює інтерфейс при додаванні елементів
        public ObservableCollection<Employee> Employees { get; set; }

        public MainWindow()
        {
            InitializeComponent();

            Employees = new ObservableCollection<Employee>();

            //  додамо одного працівника
            Employees.Add(new Employee("Іван Петренко", "Менеджер", 160));

            // Прив'язка даних (Data Binding)
            EmployeesList.ItemsSource = Employees;
        }

        private void AddEmployee_Click(object sender, RoutedEventArgs e)
        {
            // Вимога: Багатовіконний інтерфейс
            var addWindow = new AddEmployeeWindow();

            // ShowDialog відкриває вікно як модальне (діалогове)
            if (addWindow.ShowDialog() == true)
            {
                if (addWindow.NewEmployee != null)
                {
                    Employees.Add(addWindow.NewEmployee);
                }
            }
        }
    }
}