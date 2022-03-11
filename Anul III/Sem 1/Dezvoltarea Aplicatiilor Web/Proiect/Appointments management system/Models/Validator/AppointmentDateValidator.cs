using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace Appointments_management_system.Models.Validator
{
    public class AppointmentDateValidator : ValidationAttribute
    {
        protected override ValidationResult IsValid(object value, ValidationContext validationContext)
        {
            var appointment = (Models.Appointment)validationContext.ObjectInstance;
            DateTime appointmentDate = appointment.AppointmentDate;

            // cannot make an appointment later than 3 months from this date
            var maximumAppointment = DateTime.Now.AddMonths(3);

            if (appointmentDate < DateTime.Now.AddSeconds(-5 * 60))
            {
                return new ValidationResult("Cannot make an appointment in the past!");
            }
            else if (appointmentDate > maximumAppointment)
            {
                return new ValidationResult("Cannot make an appointment later than 90 days from this moment!");
            }

            return ValidationResult.Success;
        }
    }
}