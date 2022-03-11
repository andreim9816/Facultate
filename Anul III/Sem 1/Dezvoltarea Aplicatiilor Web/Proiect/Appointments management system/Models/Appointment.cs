using Appointments_management_system.Models.Validator;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace Appointments_management_system.Models
{
    public class Appointment
    {
        [Key]
        public int AppointmentId { get; set; }

        [Required(ErrorMessage = "Appointment must be set")]
        [AppointmentDateValidator]
        public DateTime AppointmentDate { get; set; }

        [Required(ErrorMessage = "Hour must be set")]
        public string AppointmentHour { get; set; }

        [Required(ErrorMessage = "Please type in a short description for the appointment")]
        [MinLength(10, ErrorMessage = "Description cannot be less than 10 characters!"),
        MaxLength(200, ErrorMessage = "Description cannot be more than 200 characters!")]
        public string Details { get; set; }

        //one-to-many relationship
        public int DoctorId { get; set; }
        public virtual Doctor Doctor { get; set; }
        //one-to-many relationship
        public string ApplicationUserId { get; set; }
        public virtual ApplicationUser ApplicationUser { get; set; }
    }
}