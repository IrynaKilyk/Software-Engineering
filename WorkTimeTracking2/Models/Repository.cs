using System.Collections.ObjectModel;

namespace WorkTimeTracking.Models
{
    public static class Repository
    {
        // static означає, що цей список спільний для всієї програми
        public static ObservableCollection<Employee> Employees { get; set; } = new ObservableCollection<Employee>();
        // НОВА КОЛЕКЦІЯ ДЛЯ ЗАЯВОК
        public static ObservableCollection<TimeRequest> Requests { get; set; } = new ObservableCollection<TimeRequest>();
        static Repository()
        {
            // Додамо тестових даних, щоб було під ким заходити
            Employees.Add(new Employee("Іван", "Коваль", "Менеджер", 160, "1234", true));
            Employees.Add(new Employee("Олена", "Бондар", "Дизайнер", 145, "0000", true));
        }
    }
}