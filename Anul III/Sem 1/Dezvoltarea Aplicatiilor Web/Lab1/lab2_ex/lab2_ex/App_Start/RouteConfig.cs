using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;

namespace lab2_ex
{
    public class RouteConfig
    {
        public static void RegisterRoutes(RouteCollection routes)
        {
            routes.IgnoreRoute("{resource}.axd/{*pathInfo}");
            routes.MapMvcAttributeRoutes();
            
            routes.MapRoute(
               name: "SearchSequenceExercise",
               url: "Exercises/Ex1/{word}/{sentence}",
               defaults: new { controller = "Exercises", action = "SearchSequence", word = UrlParameter.Optional, sentence = UrlParameter.Optional }
           );

            routes.MapRoute(
                name: "SearchSequenceOptional",
                url: "Exercises/Ex2/{word}/{sentence}",
                defaults: new { controller = "Exercises", action = "SearchSequenceOptional", word = UrlParameter.Optional, sentence = UrlParameter.Optional }
            );

            routes.MapRoute(
              name: "RegexParserExercise",
              url: "Exercises/Ex3/{number}",
              defaults: new { controller = "Exercises", action = "NumberRegexParser", number = UrlParameter.Optional},
              constraints: new {number = @"^\d{2,6}[02468]$"}
          );

            routes.MapRoute(
                name: "Default",
                url: "{controller}/{action}/{id}",
                defaults: new { controller = "Home", action = "Index", id = UrlParameter.Optional }
            );
        }
    }
}
