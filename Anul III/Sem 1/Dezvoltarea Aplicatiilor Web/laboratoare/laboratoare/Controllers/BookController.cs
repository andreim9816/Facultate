using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Data.Entity;
using laboratoare.Models;

namespace laboratoare.Controllers
{
    public class BookController : Controller
    {
        private DbCtx db = new DbCtx();
        // GET: Book
        public ActionResult Index()
        {
            List<Book> books = db.Books.Include("Publisher").ToList();
            ViewBag.Books = books;

            return View();
        }

        public ActionResult Details(int? id)
        {
            if (id.HasValue)
            {
                Book book = db.Books.Find(id);
                if (book != null)
                {
                    return View(book);
                }
                else
                {
                    return HttpNotFound("Could not find the book with the id " + id + "");
                }
            }
            return HttpNotFound("Missing book id!");
        }

        public ActionResult New()
        {
            Book book = new Book();
            book.Genres = new List<Genre>();
            return View(book);
        }

        [HttpPost]
        public ActionResult New(Book bookRequest)
        {
            try
            {
                if (ModelState.IsValid)
                {
                    bookRequest.Publisher = db.Publishers
                        .FirstOrDefault(p => p.PublisherId.Equals(1));

                    db.Books.Add(bookRequest);
                    db.SaveChanges();
                    return RedirectToAction("Index");
                }
                return View(bookRequest);
            } catch (Exception e)
            {
                return View(bookRequest);
            }
        }

        [HttpGet]
        public ActionResult Edit(int? id)
        {
            if (id.HasValue)
            {
                Book book = db.Books.Find(id);
                if (book == null)
                {
                    return HttpNotFound("Could not find the book with the id " + id.ToString());
                }
                return View(book);
            }
            return HttpNotFound("Missing parameter!");
        }

        [HttpPut] 
        public ActionResult Edit(int id, Book bookRequest)
        {
            try
            {
                if(ModelState.IsValid)
                {
                    Book book = db.Books
                        .Include("Publisher")
                        .SingleOrDefault(b => b.BookId.Equals(id));

                    if(TryUpdateModel(book))
                    {
                        book.Title = bookRequest.Title;
                        book.Author = bookRequest.Author;
                        book.Summary = bookRequest.Summary;
                        db.SaveChanges();
                    }
                    return RedirectToAction("Index");
                }
                return View(bookRequest);
            }catch(Exception e)
            {
                return View(bookRequest);
            }
        }
    }
}