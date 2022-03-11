using FoodForYouApp.Entities;
using FoodForYouApp.Managers;
using FoodForYouApp.Models;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FoodForYouApp.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class OrderFoodAndDrinkController : ControllerBase
    {
        private readonly IOrderFoodAndDrinksManager manager;

        public OrderFoodAndDrinkController(IOrderFoodAndDrinksManager foodManager)
        {
            this.manager = foodManager;
        }

        [HttpGet("OrderFoodAndDrinks")]
        public async Task<IActionResult> GetFoodAndDrinks()
        {
            var food = manager.GetFoodAndDrinks();

            return Ok(food);
        }

        [HttpPost("AddFoodAndDrink")]
        public async Task<IActionResult> Create([FromBody] OrderFoodAndDrinkModel foodModel)
        {
            var newfood = new OrderFoodAndDrink
            {
                OrderId = foodModel.OrderId,
                FoodAndDrinkId = foodModel.FoodAndDrinkId,
                PreparationTime = foodModel.PreparationTime,
                NumberOfProducts = foodModel.NumberOfProducts
            };

            manager.Create(newfood);
            return Ok();
        }
    }
}
