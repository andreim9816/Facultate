using examen.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace examen.Controllers
{
    public class PoezieController : Controller
    {
        private DbCtx DbCtx = new DbCtx();
        public ActionResult Index()
        {
            List<Poezie> list = DbCtx.Poezii.ToList();
            ViewBag.list = list;
            return View();
        }

        public ActionResult New()
        {
            Poezie poezie = new Poezie();
            poezie.VolumeList = GetAllVolume();
            return View(poezie);
        }

        [HttpPost]
        public ActionResult New(Poezie request)
        {
            try
            {
                request.VolumeList = GetAllVolume();

                if (ModelState.IsValid)
                {
                    DbCtx.Poezii.Add(request);
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
        public ActionResult Edit(int? id)
        {
            if (id.HasValue)
            {
                Poezie poezie = DbCtx.Poezii.Find(id);
                if (poezie == null)
                {
                    return HttpNotFound("Nu exista poezie cu id-ul " + id.ToString() + "!");
                }
                poezie.VolumeList = GetAllVolume();

                return View(poezie);
            }
            return HttpNotFound("Lipeste parametrul id!");
        }

        [HttpPut]
        public ActionResult Edit(int id, Poezie request)
        {
            try
            {
                request.VolumeList = GetAllVolume();
                if (ModelState.IsValid)
                {
                    Poezie poezie = DbCtx.Poezii.Find(id);

                    if (TryUpdateModel(poezie))
                    {
                        poezie.Titlu = request.Titlu;
                        poezie.Autor = request.Autor;
                        poezie.NrStrofe = request.NrStrofe;
                        poezie.VolumId = request.VolumId;

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
        public ActionResult Delete(int id)
        {
            Poezie poezie = DbCtx.Poezii.Find(id);
            if (poezie != null)
            {
                DbCtx.Poezii.Remove(poezie);
                DbCtx.SaveChanges();
                return RedirectToAction("Index");
            }
            return HttpNotFound("Nu exista poezie cu id-ul " + id.ToString() + "!");
        }

        [Route("Poezie/CautareSubstringPoezie/{cuvant?}")]
        public ActionResult CautareSubstringPoezie(string? cuvant)
        {

            if (cuvant != null)
            {
                var poezii = DbCtx.Poezii.Where(poezie => poezie.Titlu.ToLower().Contains(cuvant.ToLower())).ToList();
                ViewBag.list = poezii;
                ViewBag.cuvant = cuvant;
                return View();
            }
            return Content("Introdu un cuvant!!!");
        }

        [Route("Poezie/CautareSubstringVolum/{cuvant?}")]

        public ActionResult CautareSubstringVolum(string? cuvant)
        {

            if (cuvant != null)
            {
                var poezii = DbCtx.Poezii.Where(poezie => poezie.Volum.Denumire.ToLower().Contains(cuvant.ToLower())).ToList();
                ViewBag.list = poezii;
                ViewBag.cuvant = cuvant;
                return View();
            }
            return Content("Introdu un cuvant!!!");
        }

        // ultimul ex
        public ActionResult CautareAvansata()
        {
            PoezieVolumViewModel vb = new PoezieVolumViewModel();
            return View(vb);
        }

        [HttpPost]
        public ActionResult AfiseazaRezultate(PoezieVolumViewModel vm)
        {
            if (ModelState.IsValid)
            {
                var poezii = DbCtx.Poezii
                    .Where(poezie => poezie.Volum.Denumire.ToLower().Contains(vm.DenumireVolum.ToLower()))
                    .Where(poezie => poezie.Titlu.ToLower().Contains(vm.Titlu.ToLower()))
                    .ToList();

                ViewBag.list = poezii;

                return View("Index");
            }
            return View("CautareAvansata", vm);
        }

        [NonAction]
        public IEnumerable<SelectListItem> GetAllVolume()
        {

            var selectList = new List<SelectListItem>();
            foreach (var volum in DbCtx.Volume.ToList())
            {
                selectList.Add(new SelectListItem
                {
                    Value = volum.Id.ToString(),
                    Text = volum.Denumire
                });
            }
            return selectList;
        }
    }
}