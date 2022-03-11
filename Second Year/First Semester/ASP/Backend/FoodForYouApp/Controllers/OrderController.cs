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
    public class OrderController : ControllerBase
    {
        private readonly IOrdersManager manager;

        public OrderController(IOrdersManager clientsManager)
        {
            this.manager = clientsManager;
        }

        [HttpGet("AllOrders")]
        public async Task<IActionResult> GetOrders()
        {
            var orders = manager.GetOrders();

            return Ok(orders);
        }

        [HttpGet("GetOrderbyId/{id}")]
        public async Task<IActionResult> GetById([FromRoute] string id)
        {
            var order = manager.GetOrderById(id);

            return Ok(order);
        }

        [HttpGet("OrdersWithFood")]
        public async Task<IActionResult> GetOrdersWithFood()
        {
            var orderswithfood = manager.GetOrdersWithFood();

            return Ok(orderswithfood);
        }

        [HttpPost("AddOrder")]
        public async Task<IActionResult> Create([FromBody] OrderModel orderModel)
        {
            var newOrder = new Order
            {
                Id = orderModel.Id,
                PaymentMethod = orderModel.PaymentMethod,
                OrderDate = orderModel.OrderDate,
                Address = orderModel.Address,
                ClientId = orderModel.ClientId
            };

            manager.Create(newOrder);
            return Ok();
        }

        [HttpPut("UpdateOrder")]
        public async Task<IActionResult> Update([FromBody] OrderModel orderModel)
        {
            manager.Update(orderModel);

            return Ok();
        }
        [HttpDelete("DeleteOrder{id}")]
        public async Task<IActionResult> Delete([FromRoute] string id)
        {
            manager.Delete(id);

            return Ok();
        }
    }
}
