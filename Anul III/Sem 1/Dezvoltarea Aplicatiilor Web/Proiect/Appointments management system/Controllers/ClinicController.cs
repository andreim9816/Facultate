using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Data.Entity;
using Appointments_management_system.Models;

namespace Appointments_management_system.Controllers
{
    [Authorize(Roles = "Admin")]
    public class ClinicController : Controller
    {
        private ApplicationDbContext DbCtx = new ApplicationDbContext();

        [HttpGet]
        [AllowAnonymous]
        public ActionResult Index()
        {
            List<Clinic> clinics = DbCtx.Clinics.ToList();
            ViewBag.clinics = clinics;
            return View();

        }

        [HttpGet]
        public ActionResult New()
        {
            ClinicAddressViewModel clinicAddressViewModel = new ClinicAddressViewModel();
            clinicAddressViewModel.SpecialityList = GetAllSpecialities();
            return View(clinicAddressViewModel);
        }

        [HttpPost]
        public ActionResult New(ClinicAddressViewModel objectRequest)
        {
            try
            {
                if (ModelState.IsValid)
                {
                    var selectedSpecialities = objectRequest.SpecialityList.Where(obj => obj.IsChecked).ToList();
                    Address address = new Address
                    {
                        Street = objectRequest.Street,
                        No = objectRequest.No,
                        City = objectRequest.City
                    };

                    Clinic clinic = new Clinic
                    {
                        PhoneNumber = objectRequest.PhoneNumber,
                        Name = objectRequest.Name,
                        Address = address,
                        Specialities = new List<Speciality>()
                    };

                    foreach(var spec in selectedSpecialities)
                    {
                        Speciality speciality = DbCtx.Specialities.Find(spec.Id);
                        clinic.Specialities.Add(speciality);
                    }

                    DbCtx.Addresses.Add(address);
                    DbCtx.Clinics.Add(clinic);
                    DbCtx.SaveChanges();
                    return RedirectToAction("Index", "Clinic");
                }
                return View(objectRequest);
            }
            catch (Exception e)
            {
                return View(objectRequest);
            }
        }

        [HttpGet]
        [AllowAnonymous]
        public ActionResult Details(int? id)
        {
            if (id.HasValue)
            {
                Clinic clinic = DbCtx.Clinics.Find(id);
                if (clinic != null)
                {
                    return View(clinic);
                }
                return HttpNotFound("Couldn't find the clinic with id " + id.ToString() + "!");
            }
            return HttpNotFound("Missing clinic id parameter!");
        }

        [HttpGet]
        [AllowAnonymous]
        public ActionResult Specialities(int? id)
        {
            /* For a specific Clinic, get all its specialities */
            if (id.HasValue)
            {
                Clinic clinic = DbCtx.Clinics.Find(id);

                if (clinic == null)
                {
                    return HttpNotFound("Couldn't find the clinic with id = " + id.ToString() + "!");
                }
                return View(clinic);
            }
            return HttpNotFound("Missing clinic id parameter!");
        }

        [HttpGet]
        [Authorize(Roles ="Admin")]
        public ActionResult Edit(int? id)
        {
            if (id.HasValue)
            {
                Clinic clinic = DbCtx.Clinics.Find(id);

                if (clinic == null)
                {
                    return HttpNotFound("Couldn't find the clinic with id = " + id.ToString() + "!");
                }

                ViewBag.id = id;

                ClinicAddressViewModel vm = new ClinicAddressViewModel
                {
                    Name = clinic.Name,
                    PhoneNumber = clinic.PhoneNumber,
                    City = clinic.Address.City,
                    No = clinic.Address.No,
                    Street = clinic.Address.Street,
                    SpecialityList = GetAllSpecialities()
                };

                foreach(Speciality spec in clinic.Specialities)
                {
                    vm.SpecialityList.FirstOrDefault(obj => obj.Id == spec.SpecialityId).IsChecked = true;
                }

                return View(vm);
            }
            return HttpNotFound("Missing clinic id parameter!");
        }

        [HttpPut]
        [Authorize(Roles = "Admin")]
        public ActionResult Edit(int id, ClinicAddressViewModel request)
        {
            try
            {
                if (ModelState.IsValid)
                {
                    Clinic clinic = DbCtx.Clinics.Find(id);
                    var selectedSpecialities = request.SpecialityList.Where(obj => obj.IsChecked).ToList();

                    if (TryUpdateModel(clinic))
                    {
                        clinic.Name = request.Name;
                        clinic.PhoneNumber = request.PhoneNumber;
                        clinic.Address.Street = request.Street;
                        clinic.Address.No = request.No;
                        clinic.Address.City = request.City;

                        clinic.Specialities.Clear();
                        clinic.Specialities = new List<Speciality>();

                        for(int i = 0; i < selectedSpecialities.Count(); i++)
                        {
                            Speciality speciality = DbCtx.Specialities.Find(selectedSpecialities[i].Id);
                            clinic.Specialities.Add(speciality);
                        }
                        DbCtx.SaveChanges();
                    }
                    return RedirectToAction("Index", "Clinic");
                }
                return View(request);
            }
            catch (Exception e)
            {
                return View(request);
            }
        }

        [HttpDelete]
        [Authorize(Roles = "Admin")]
        public ActionResult Delete(int? id)
        {
            if (id.HasValue)
            {
                Clinic clinic = DbCtx.Clinics.Find(id);
                if (clinic == null)
                {
                    return HttpNotFound("Couldn't find the clinic with id = " + id.ToString() + "!");
                }
                DbCtx.Addresses.Remove(clinic.Address);
                DbCtx.Clinics.Remove(clinic);

                DbCtx.SaveChanges();
                return RedirectToAction("Index", "Clinic");
            }
            return HttpNotFound("Missing clinic id parameter!");
        }

        [NonAction]
        public List<CheckBoxSpecialityViewModel> GetAllSpecialities()
        {
            var checkBoxList = new List<CheckBoxSpecialityViewModel>();
            foreach (var spec in DbCtx.Specialities.ToList())
            {
                checkBoxList.Add(new CheckBoxSpecialityViewModel
                {
                    Id = spec.SpecialityId,
                    Name = spec.SpecialityName,
                    IsChecked = false
                });
            }
            return checkBoxList;
        }
    }
}