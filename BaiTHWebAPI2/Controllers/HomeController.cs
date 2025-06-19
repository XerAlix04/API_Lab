using Microsoft.AspNetCore.Mvc;

namespace BaiTHWebAPI2.Controllers
{
    public class HomeController : Controller
    {
        public IActionResult Index()
        {
            return new ContentResult
            {
                ContentType = "text/html",
                Content = System.IO.File.ReadAllText(Path.Combine(Directory.GetCurrentDirectory(), "wwwroot", "index.html"))
            };
        }
    }
}
