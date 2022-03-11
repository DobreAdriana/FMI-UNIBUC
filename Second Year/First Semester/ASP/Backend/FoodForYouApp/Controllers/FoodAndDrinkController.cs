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
    public class FoodAndDrinkController : ControllerBase
    {
        private readonly IFoodAndDrinksManager manager;

        public FoodAndDrinkController(IFoodAndDrinksManager foodManager)
        {
            this.manager = foodManager;
        }

        [HttpGet("FoodAndDrinks")]
        public async Task<IActionResult> GetFoodAndDrinks()
        {
            var food = manager.GetFoodAndDrinks();

            return Ok(food);
        }

        [HttpGet("GetFoodAndDrinkbyId/{id}")]
        public async Task<IActionResult> GetById([FromRoute] string id)
        {
            var food = manager.GetFoodAndDrinkById(id);

            return Ok(food);
        }

        [HttpPost("AddFoodAndDrink")]
        public async Task<IActionResult> Create([FromBody] FoodAndDrinkModel foodModel)
        {
            var newfood = new FoodAndDrink
            {
                Id = foodModel.Id,
                Name = foodModel.Name,
                Price = foodModel.Price,
                Observations = foodModel.Observations
            };

            manager.Create(newfood);
            return Ok();
        }

        [HttpPut("UpdateFoodAndDrink")]
        public async Task<IActionResult> Update([FromBody] FoodAndDrinkModel foodModel)
        {
            manager.Update(foodModel);

            return Ok();
        }
        [HttpDelete("DeleteFoodAndDrink{id}")]
        public async Task<IActionResult> Delete([FromRoute] string id)
        {
            manager.Delete(id);

            return Ok();
        }
    }
}
