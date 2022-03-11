using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using Appointments_management_system.Models;

namespace Appointments_management_system.Controllers
{
    [Authorize(Roles = "Admin")]
    public class SpecialityController : Controller
    {
        ApplicationDbContext DbCtx = new ApplicationDbContext();

        [HttpGet]
        [AllowAnonymous]
        public ActionResult Index()
        {
            List<Speciality> specialities = DbCtx.Specialities.ToList();
            ViewBag.specialities = specialities;
            return View();
        }

        [HttpGet]
        public ActionResult New()
        {
            Speciality speciality = new Speciality();
            return View(speciality);
        }

        [HttpPost]
        public ActionResult New(Speciality request)
        {
            try
            {
                if (ModelState.IsValid)
                {
                    Speciality speciality = new Speciality();
                    speciality.Clinics = new List<Clinic>();
                    speciality.SpecialityName = request.SpecialityName;

                    DbCtx.Specialities.Add(speciality);
                    DbCtx.SaveChanges();
                    return RedirectToAction("Index");
                }
                return View(request);
            }
            catch (Exception e)
            {
                return View(request);
            }
        }

        [HttpGet]
        public ActionResult AddClinic(int? id)
        {
            if (id.HasValue)
            {
                Speciality speciality = DbCtx.Specialities.Find(id);
                if (speciality == null)
                {
                    return HttpNotFound("Couldn't find the speciality with id = " + id.ToString() + "!");
                }

                List<Clinic> clinics = DbCtx.Clinics.ToList();
                ViewBag.clinics = clinics;
                ViewBag.Name = speciality.SpecialityName;
                return View();
            }
            return HttpNotFound("Missing speciality id parameter!");
        }

        [HttpGet]
        public ActionResult Edit(int? id)
        {
            if (id.HasValue)
            {
                Speciality speciality = DbCtx.Specialities.Find(id);

                if (speciality == null)
                {
                    return HttpNotFound("Couldn't find the speciality with id = " + id.ToString() + "!");
                }
                return View(speciality);
            }
            return HttpNotFound("Missing speciality id parameter!");
        }

        [HttpGet]
        [AllowAnonymous]
        public ActionResult Clinics(int? id)
        {
            // get all the clinics within a clinic 
            if (id.HasValue)
            {
                Speciality speciality = DbCtx.Specialities.Find(id);

                if (speciality == null)
                {
                    return HttpNotFound("Couldn't find the speciality with id = " + id.ToString() + "!");
                }
                return View(speciality);
            }
            return HttpNotFound("Missing speciality id parameter!");
        }

        [HttpPut]
        public ActionResult Edit(int id, Speciality request)
        {
            try
            {
                if (ModelState.IsValid)
                {
                    Speciality speciality = DbCtx.Specialities.Find(id);

                    if (TryUpdateModel(speciality))
                    {
                        speciality.SpecialityName = request.SpecialityName;
                        DbCtx.SaveChanges();
                    }
                    return RedirectToAction("Index");
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
                Speciality speciality = DbCtx.Specialities.Find(id);
                if (speciality == null)
                {
                    return HttpNotFound("Couldn't find the speciality with the id " + id.ToString() + "!");
                }
                DbCtx.Specialities.Remove(speciality);
                foreach (var doctor in DbCtx.Doctors)
                {
                    if (doctor.SpecialityId == id)
                    {
                        DbCtx.Doctors.Remove(doctor);
                    }
                }
                DbCtx.SaveChanges();
                return RedirectToAction("Index");

            }
            return HttpNotFound("Missing speciality id parameter!");
        }


        public JsonResult GetAllClinicsFromSpeciality(int id)
        {
            Speciality spec = DbCtx.Specialities.Find(id);

            var selectList = spec.Clinics.Select(c => new
            {
                Value = c.ClinicId.ToString(),
                Text = c.Name
            });

          /*  foreach (var clinic in spec.Clinics)
            {
                selectList.Add(new SelectListItem
                {
                    Value = clinic.ClinicId.ToString(),
                    Text = clinic.Name
                });
            }*/
            return Json(selectList, JsonRequestBehavior.AllowGet);
        }
    }
}