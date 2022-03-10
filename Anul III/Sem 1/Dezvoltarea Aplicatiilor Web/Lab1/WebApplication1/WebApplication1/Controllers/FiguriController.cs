using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using WebApplication1.Models;

namespace WebApplication1.Controllers
{
    public class FiguriController : Controller
    {
        // GET: Figuri
        public ActionResult Index()
        {
            return View();
        }

        public ActionResult Prima()
        {
            Figura f = new Figura();
            f.Nume = "cerc";
            return View(f);

        }
    }
}