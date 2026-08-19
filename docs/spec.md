## Order

An order is simply a request to buy or sell something.

The "Order" is an object with fields:
Order ID 
Side (BUY/SELL)
Price
Quantity
Time

This will be implemented as a struct with a constructor included. I am including a constructor because values are normalized during creation, input can be validated, required information cannot be accidentally omitted.

On the buy side, this means the person is willing to pay up to $x for a share, so <= $x.

On the sell side, the person is willing to sell their share for no less than $y, so >= $y.

Better price is prioritized.

If the prices are equal, earlier order goes first.

Partially filled orders stay in the queue with their remaining quantity.

Unmatched orders means that the seller's price is higher than the incoming buy order, or the buyer's price is lower than the incoming sell order. As a result, no trade happens; the incoming order gets added to the queue.

If there's a cancellation, the order is removed from the queue.

Trades happen at the resting price.

For example, if theres a buyer already in the queue:
BUY $100 7 shares

and an incoming seller:
SELL $98 7 shares

Since a trade can happen, it will be executed at $100 because an incoming order matches against the price already available in the book.

Active order IDs will be tracked for the duration of their lifetime. If the user inputs an existing ID, there will be an error and the user will have to input a different ID. Once a trade happens, fully filled order ID's are removed from the map.

If an order is cancelled, the person who cancelled it will have their order ID removed from the map.

Cancelling an order that doesn't exist will throw an error.

If one incoming order fills several resting orders, the filled orders will be removed from the queue.

Each trade reports the buyer ID, seller ID, execution price, executed quantity, and remaining quantity of any partially filled order.

Time will be updated by the order book, not by the caller. It will have a default value of 0.

## Order Book

OrderBook will be implemented as a class, with private members being buyOrders, sellOrders, active IDs and time. Public members being methods like adding or cancelling an order.

BUY side needs prices ordered in descending order. SELL side needs prices ordered in ascending order.
Best price and earliest time is needed for sorted order.

This will be implemented using a ordered map, with the keys being the prices and the values being a deque of orders.

We will use one for BUY side and one for SELL side.

We will also keep track of active IDs using an unordered map, with the key being the ID and value being the price and side (BUY/SELL).

Methods for the class include addOrder and cancelOrder, which will both be void.

Time will be incremented each time a new order is added to the queue. 

## Matching Engine

The matching engine looks at incoming orders and decides whether they can trade with orders already waiting in the order book.

It asks if this new order trade with someone already waiting.

If yes, it creates a trade. If not, the new order gets added to the order book.

When a order is added to the book, through the addOrder function, it's checked if its a valid order (the ID doesn't already exist).

If it's a valid order, it's then checked if it's a BUY or SELL order.

If it's a valid BUY order, the matchBuy function is called.

The incoming BUY order is compared with the best resting SELL order. 

If BUY price >= SELL price, a trade can happen at the resting SELL price.

A trade is executed at the minimum of the incoming BUY shares and resting SELL shares.

If the incoming BUY order has shares left and the resting SELL order doesn't after execution, the resting SELL order is removed from the book and the activeIDs map. If there are anymore resting orders in the SELL book, the process is repeated until there the incoming BUY order has no shares left, no trade can happen or there are no SELL orders left. If no trade can happen or there are no SELL orders left, the BUY order is added to the book.

If the incoming BUY order has no shares left, it never gets added to the book. The resting SELL stays at the front of the deque and the quantity gets updated accordingly, while keeping its original priority/time.

If it's a valid SELL order, the matchSell function is called.

The incoming SELL order is compared with the best resting BUY order. 

If SELL price <= BUY price, a trade can happen at the resting BUY price.

A trade is executed at the minimum of the SELL shares and resting BUY shares.

If the incoming SELL order has shares left and the resting BUY order doesn't after execution, the resting BUY order is removed from the book and the activeIDs map. If there are anymore resting orders in the BUY book, the process is repeated until there the incoming BUY order has no shares left, no trade can happen or there are no BUY orders left. If no trade can happen or there are no BUY orders left, the SELL order is added to the book.

If the incoming SELL order has no shares left, it never gets added to the book. The resting BUY stays at the front of the deque and the quantity gets updated accordingly, while keeping its original priority/time.