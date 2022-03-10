using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace lab2_ex.Controllers
{
    public class ExercisesController : Controller
    {
        public ContentResult SearchSequence(string word, string sentence)
        {
            string message = "Sentence " + sentence + " contains the word " + word;
            string message2 = "Sentence " + sentence + " does NOT contain the word " + word;
            string errorMessage = "A parameter is missing!";

            if(word != null && sentence != null)
            {
                if(sentence.Contains(word))
                {
                    return Content(message);
                }
                return Content(message2);
            }
            return Content(errorMessage);
        }

        public ActionResult SearchSequenceOptional(string word, string? sentence)
        {
            ViewBag.message = "Sentence " + sentence + " does NOT contain the word " + word;
            if(word == null)
            {
                ViewBag.message = "A parameter is missing";
            }
            
            if(sentence == null)
            {
                return HttpNotFound("A parameter is missing");
            }

            if(sentence.Contains(word))
            {
                return ViewBag.message = "Sentence " + sentence + " contains the word " + word;
            }

            return View();
        }

        public string NumberRegexParser(int? number)
        {
            return "The input number is: " + number.ToString();
        }

        [Route("LanguageRegexParser/{input:regex(^(a+)(b+)$)}")]
        public string RegexParser(string? input)
        {
            return "The input is: " + input;
        }
    }
}