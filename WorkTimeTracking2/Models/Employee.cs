namespace WorkTimeTracking.Models
{
    public class Employee
    {
        // Вимога: Поля класів повинні містити методи GET та SET
        public string Name { get; set; }
        public string Position { get; set; }
        public int HoursWorked { get; set; }

        // Конструктор для зручності
        public Employee(string name, string position, int hours)
        {
            Name = name;
            Position = position;
            HoursWorked = hours;
        }

        // Перевизначимо ToString, щоб у списку гарно відображалось, якщо DataTemplate не спрацює
        public override string ToString()
        {
            return $"{Name} ({Position}) - {HoursWorked} год.";
        }
    }
}