using Appointments_management_system.Models;
using Microsoft.AspNet.Identity;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Appointments_management_system.Controllers
{
    [Authorize]
    public class AppointmentController : Controller
    {
        private ApplicationDbContext DbCtx = new ApplicationDbContext();

        [HttpGet]
        public ActionResult Index()
        {
            List<Appointment> appointmentList = new List<Appointment>();
            if (User.IsInRole("User"))
            {
                var userId = this.User.Identity.GetUserId();
                appointmentList = DbCtx.Appointments.Where(obj => obj.ApplicationUserId == userId).ToList();
            }
            else if (User.IsInRole("Admin"))
            {
                appointmentList = DbCtx.Appointments.ToList();
            }
            

            ViewBag.appointmentList = appointmentList;
            return View();
        }


        [HttpGet]
        [Authorize(Roles = "User")]
        public ActionResult New(int? id)
        {
            if (id.HasValue)
            {
                Doctor doctor = DbCtx.Doctors.Find(id);

                if (doctor == null)
                {
                    return HttpNotFound("There is no doctor with this id!");
                }

                AppointmentRequestModel appointmentRequestModel = new AppointmentRequestModel
                {
                    DoctorId = (int)id,
                    Date = DateTime.Now,
                    ChosenAppointmentHour = "00:00",
                    AppointmentHours = new List<SelectListItem>(),
                    DoctorFirstName = doctor.FirstName,
                    DoctorLastName = doctor.LastName,
                    City = doctor.Clinic.Address.City,
                    ClinicName = doctor.Clinic.Name
            };

                return View(appointmentRequestModel);
            }
            return HttpNotFound("Missing doctor id parameter!");
        }

        [HttpPost]
        [Authorize(Roles = "User")]
        public ActionResult New(AppointmentRequestModel request)
        {
            try
            {
                request.AppointmentHours = new List<SelectListItem>();
                if (ModelState.IsValid)
                {
                    Appointment appointment = new Appointment
                    {
                        DoctorId = request.DoctorId,
                        AppointmentDate = request.Date,
                        Details = request.Details,
                        AppointmentHour = request.ChosenAppointmentHour,
                        ApplicationUserId = this.User.Identity.GetUserId()
                    };

                    DbCtx.Appointments.Add(appointment);

                    DbCtx.SaveChanges();
                    return RedirectToAction("Index", "Clinic");
                }
                return View(request);
            }
            catch (Exception e)
            {
                return View(request);
            }
        }

        [HttpGet]
        [Authorize(Roles = "User,Admin")]
        public ActionResult Edit(int? id)
        {
            if (id.HasValue)
            {
                Appointment appointment = DbCtx.Appointments.Find(id);

                if (appointment == null)
                {
                    return HttpNotFound("Couldn't find the appointment with id = " + id.ToString() + "!");
                }

                if(appointment.ApplicationUserId != this.User.Identity.GetUserId() && !User.IsInRole("Admin"))
                {
                    return RedirectToAction("Index", "Appointment");
                }

                AppointmentRequestModel request = new AppointmentRequestModel
                {
                    AppointmentId = (int)id,
                    DoctorId = appointment.DoctorId,
                    ClinicName = appointment.Doctor.Clinic.Name,
                    City = appointment.Doctor.Clinic.Address.City,
                    DoctorLastName = appointment.Doctor.LastName,
                    DoctorFirstName = appointment.Doctor.FirstName,
                    Date = appointment.AppointmentDate,
                    Details = appointment.Details,
                    ChosenAppointmentHour = appointment.AppointmentHour,
                  //  AppointmentHours = GetAllAvailableHoursForEdit(appointment.AppointmentDate, appointment.DoctorId
                    AppointmentHours = new List<SelectListItem>()
                };

                return View(request);
            }
            return HttpNotFound("Missing appointment id parameter!");
        }

        [HttpPut]
        [Authorize(Roles = "User,Admin")]
        public ActionResult Edit(int id, AppointmentRequestModel request)
        {
            try
            {
                request.AppointmentHours = new List<SelectListItem>();
                if (ModelState.IsValid)
                {
                    Appointment appointment = DbCtx.Appointments.Find(id);

                    if (TryValidateModel(appointment))
                    {
                        appointment.AppointmentDate = request.Date;
                        appointment.AppointmentHour = request.ChosenAppointmentHour;
                        appointment.Details = request.Details;

                        DbCtx.SaveChanges();
                    }
                    return RedirectToAction("Index", "Appointment");
                }
                return View(request);
            }
            catch (Exception e)
            {
                return View(request);
            }
        }

        [HttpGet]
        [Authorize(Roles = "User,Admin")]
        public ActionResult Details(int? id)
        {
            if (id.HasValue)
            {
                Appointment appointment = DbCtx.Appointments.Find(id);
                if (appointment == null)
                {
                    return HttpNotFound("Couldn't find the appointment with id " + id.ToString() + "!");
                }

                if (User.Identity.GetUserId() == appointment.ApplicationUserId || User.IsInRole("Admin"))
                {
                    Speciality speciality = DbCtx.Specialities.Find(appointment.Doctor.SpecialityId);

                    ViewBag.SpecialityName = speciality.SpecialityName;
                    return View(appointment);
                }
                return RedirectToAction("Index", "Appointment");
            }
            return HttpNotFound("Missing appointment id parameter!");
        }


        [HttpDelete]
        public ActionResult Delete(int? id)
        {
            if (id.HasValue)
            {
                Appointment appointment = DbCtx.Appointments.Find(id);
                if (appointment == null)
                {
                    return HttpNotFound("Couldn't find the appointment with id = " + id.ToString() + "!");
                }

                if (User.Identity.GetUserId() == appointment.ApplicationUserId || User.IsInRole("Admin"))
                {
                    DbCtx.Appointments.Remove(appointment);
                    DbCtx.SaveChanges();
                }

                return RedirectToAction("Index", "Appointment");
            }
            return HttpNotFound("Missing appointment id parameter!");
        }

     
        public JsonResult GetAllAvailableHoursForEdit(DateTime? date, int doctorId, int appointmentId)
        {
            var selectList = new List<string>();

            var AppointmentHourList = new List<String> { "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00" };

            Doctor doctor = DbCtx.Doctors.Find(doctorId);

            if (doctor == null)
            {
                return Json(new List<string>(), JsonRequestBehavior.AllowGet);
            }

            // get the doctor's appointment list on that date
            var appointmentList = doctor.Appointments
                .Where(obj => obj.AppointmentDate == date)
                .Select(obj => obj.AppointmentHour).ToList();

            // get the available hours
            var remainingHours = AppointmentHourList.Except(appointmentList).ToList();

            // add the current appointment hour
            remainingHours.Add(DbCtx.Appointments.Find(appointmentId).AppointmentHour);

            remainingHours.Sort();

            foreach (string hour in remainingHours)
            {
                // build the dropDownList elements
                selectList.Add(hour);
            }

            return Json(selectList, JsonRequestBehavior.AllowGet);
        }

        public JsonResult GetAllAvailableHours(DateTime? date, int doctorId)
        {
            var selectList = new List<string>();
            var AppointmentHourList = new List<String> {  "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00" };

            Doctor doctor = DbCtx.Doctors.Find(doctorId);

            if (doctor == null)
            {
                return Json(new List<string>(), JsonRequestBehavior.AllowGet);
            }

            // get the doctor's appointment list on that date
            var appointmentList = doctor.Appointments
                .Where(obj => obj.AppointmentDate == date)
                .Select(obj => obj.AppointmentHour).ToList();

            // get the available hours
            var remainingHours = AppointmentHourList.Except(appointmentList).ToList();

            foreach (string hour in remainingHours)
            {
                // build the dropDownList elements
                selectList.Add(hour);
            }

            return Json(selectList, JsonRequestBehavior.AllowGet);
        }
    }
}