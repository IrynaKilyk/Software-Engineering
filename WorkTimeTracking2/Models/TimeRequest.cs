using System;

namespace WorkTimeTracking.Models
{
    public class TimeRequest
    {
        public Employee Employee { get; set; }   // Хто просить
        public string Month { get; set; }        // За який місяць
        public int Hours { get; set; }           // Скільки годин
        public string Status { get; set; }       // "Очікує", "Схвалено", "Відхилено"
        public DateTime RequestDate { get; set; }

        public string RequestInfo => $"{Month}: {Hours} год."; // Для відображення

        public TimeRequest(Employee employee, string month, int hours)
        {
            Employee = employee;
            Month = month;
            Hours = hours;
            Status = "Очікує";
            RequestDate = DateTime.Now;
        }
    }
}