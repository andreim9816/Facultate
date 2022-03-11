using System;
using System.Collections.Generic;
using System.Linq;
using Appointments_management_system.Models;
using System.Web;
using System.Web.Mvc;
using System.Diagnostics;

namespace Appointments_management_system.Controllers
{
    [Authorize(Roles = "Admin")]
    public class DoctorController : Controller
    {
        private ApplicationDbContext DbCtx = new ApplicationDbContext();

        [HttpGet]
        [AllowAnonymous]
        public ActionResult Index()
        {
            List<Doctor> Doctors = DbCtx.Doctors.ToList();
            List<String> SpecialityList = new List<string>();
            foreach (var doctor in Doctors)
            {
                Speciality spec = DbCtx.Specialities.Find(doctor.SpecialityId);
                SpecialityList.Add(spec.SpecialityName);
            }

            ViewBag.Doctors = Doctors;
            ViewBag.SpecialityList = SpecialityList;

            return View();
        }

        [HttpGet]
        [AllowAnonymous]
        public ActionResult DoctorsFilter(int? SpecialityId, int? ClinicId)
        {
            var doctorList = DbCtx.Doctors
                .Where(d => d.ClinicId == ClinicId)
                .Where(d => d.SpecialityId == SpecialityId)
                .ToList();

            var clinic = DbCtx.Clinics
                .Where(c => c.ClinicId == ClinicId)
                .FirstOrDefault<Clinic>();

            var speciality = DbCtx.Specialities
                .Where(s => s.SpecialityId == SpecialityId).
                FirstOrDefault<Speciality>();

            ViewBag.doctorList = doctorList;
            ViewBag.specialityName = speciality.SpecialityName;
            ViewBag.clinicName = clinic.Name;

            return View();
        }

        [HttpGet]
        public ActionResult New()
        {
            ClinicSpecialityDoctorViewModel vm = new ClinicSpecialityDoctorViewModel
            {
                SpecialityList = GetAllSpecialities(),
                ClinicList = new List<SelectListItem>()
            };

            return View(vm);
        }

        [HttpPost]
        public ActionResult New(ClinicSpecialityDoctorViewModel vm)
        {
            try
            {
                vm.SpecialityList = GetAllSpecialities();
                vm.ClinicList = new List<SelectListItem>();

                if (ModelState.IsValid)
                {
                    // Checks that the chosen clinic has the chosen speciality
                    Clinic clinic = DbCtx.Clinics.Find(vm.ChosenClinicId);
                    Speciality speciality = DbCtx.Specialities.Find(vm.ChosenSpecialityId);

                    if (clinic == null)
                    {
                        return HttpNotFound("Couldn't find the clinic with id " + vm.ChosenClinicId.ToString() + "!");
                    }

                    if (speciality == null)
                    {
                        return HttpNotFound("Couldn't find the speciality with id " + vm.ChosenSpecialityId.ToString() + "!");
                    }

                    var obj = (from Clinic in DbCtx.Clinics.Where(c => c.ClinicId == vm.ChosenClinicId)
                               from Speciality in Clinic.Specialities.Where(spec => spec.SpecialityId == vm.ChosenSpecialityId)
                               select Clinic).FirstOrDefault();

                    if (obj == null)
                    {
                        return HttpNotFound("Speciality " + speciality.SpecialityName + " doesn't exist in " + clinic.Name + " clinic!");
                    }

                    Doctor doctor = new Doctor
                    {
                        LastName = vm.LastName,
                        FirstName = vm.FirstName,
                        Details = vm.Details,
                        SpecialityId = vm.ChosenSpecialityId,
                        PhoneNumber = vm.PhoneNumber,
                        ClinicId = vm.ChosenClinicId
                    };

                    DbCtx.Doctors.Add(doctor);

                    DbCtx.SaveChanges();
                    return RedirectToAction("Index", "Doctor");
                }
                return View(vm);
            }
            catch (Exception e)
            {
                return View(vm);
            }
        }

        [HttpGet]
        [AllowAnonymous]
        public ActionResult Details(int? id)
        {
            if (id.HasValue)
            {
                Doctor doctor = DbCtx.Doctors.Find(id);
                Speciality speciality = DbCtx.Specialities.Find(doctor.SpecialityId);
                ViewBag.specialityName = speciality.SpecialityName;
                if (doctor != null)
                {
                    return View(doctor);
                }
                return HttpNotFound("Couldn't find the doctor with id " + id.ToString() + "!");
            }
            return HttpNotFound("Missing doctor id parameter!");
        }

        [HttpGet]
        public ActionResult Edit(int? id)
        {
            if (id.HasValue)
            {
                Doctor doctor = DbCtx.Doctors.Find(id);
                ClinicSpecialityDoctorViewModel vm = new ClinicSpecialityDoctorViewModel
                {
                    SpecialityList = GetAllSpecialities(),
                    ClinicList = new List<SelectListItem>(),
                    LastName = doctor.LastName,
                    FirstName = doctor.FirstName,
                    PhoneNumber = doctor.PhoneNumber,
                    Details = doctor.Details,
                    DoctorId = doctor.DoctorId,
                    ChosenClinicId = doctor.Clinic.ClinicId,
                    ChosenSpecialityId = doctor.SpecialityId
                };

                if (doctor == null)
                {
                    return HttpNotFound("Couldn't find the doctor with id = " + id.ToString() + "!");
                }

                return View(vm);
            }
            return HttpNotFound("Missing doctor id parameter!");
        }

        [HttpPut]
        public ActionResult Edit(int id, ClinicSpecialityDoctorViewModel request)
        {
            try
            {
                request.ClinicList = new List<SelectListItem>();
                request.SpecialityList = GetAllSpecialities();
                if (ModelState.IsValid)
                {
                    /* Checks that a clinic has the speciality */
                    Clinic clinic = DbCtx.Clinics.Find(request.ChosenClinicId);
                    Speciality speciality = DbCtx.Specialities.Find(request.ChosenSpecialityId);

                    if (clinic == null)
                    {
                        return HttpNotFound("Couldn't find the clinic with id " + request.ChosenClinicId.ToString() + "!");
                    }

                    if (speciality == null)
                    {
                        return HttpNotFound("Couldn't find the speciality with id " + request.ChosenSpecialityId.ToString() + "!");
                    }

                    var obj = (from Clinic in DbCtx.Clinics.Where(c => c.ClinicId == request.ChosenClinicId)
                               from Speciality in Clinic.Specialities.Where(spec => spec.SpecialityId == request.ChosenSpecialityId)
                               select Clinic).FirstOrDefault();

                    if (obj == null)
                    {
                        return HttpNotFound("Speciality " + speciality.SpecialityName + " doesn't exist in " + clinic.Name + " clinic!");
                    }

                    Doctor doctor = DbCtx.Doctors.Find(id);

                    if (TryValidateModel(doctor))
                    {
                        doctor.ClinicId = request.ChosenClinicId;
                        doctor.Clinic = clinic;
                        doctor.SpecialityId = request.ChosenSpecialityId;
                        doctor.FirstName = request.FirstName;
                        doctor.LastName = request.LastName;
                        doctor.PhoneNumber = request.PhoneNumber;
                        doctor.Details = request.Details;

                        DbCtx.SaveChanges();
                    }
                    return RedirectToAction("Index", "Doctor");
                }
                return View(request);
            }
            catch (Exception e)
            {
                return View(request);
            }
        }

        [HttpDelete]
        public ActionResult Delete(int? id)
        {
            if (id.HasValue)
            {
                Doctor doctor = DbCtx.Doctors.Find(id);
                if (doctor == null)
                {
                    return HttpNotFound("Couldn't find the doctor with id = " + id.ToString() + "!");
                }
                DbCtx.Doctors.Remove(doctor);
                DbCtx.SaveChanges();
                return RedirectToAction("Index", "Doctor");
            }
            return HttpNotFound("Missing doctor id parameter!");
        }

        [NonAction]
        public IEnumerable<SelectListItem> GetAllSpecialities()
        {
            var selectList = new List<SelectListItem>();
            foreach (var spec in DbCtx.Specialities.ToList())
            {
                // adaugam in lista elementele necesare pt dropdown
                selectList.Add(new SelectListItem
                {
                    Value = spec.SpecialityId.ToString(),
                    Text = spec.SpecialityName
                });
            }
            // returnam lista pentru dropdown
            return selectList;
        }

        [NonAction]
        public IEnumerable<SelectListItem> GetAllClinics()
        {
            var selectList = new List<SelectListItem>();
            foreach (var clinic in DbCtx.Clinics.ToList())
            {
                // adaugam in lista elementele necesare pt dropdown
                selectList.Add(new SelectListItem
                {
                    Value = clinic.ClinicId.ToString(),
                    Text = clinic.Name,
                });

            }
            // returnam lista pentru dropdown
            return selectList;
        }
    }
}