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

Time is the order in which the orders arrive. No actual time is being tracked.
The first order will be numbered 0, the second 1, and so on, no matter the side.

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

## Order Book

BUY side needs prices ordered in descending order. SELL side needs prices ordered in ascending order.
Best price and earliest time is needed for sorted order.

This will be implemented using a ordered map, with the keys being the prices and the values being a deque of orders.

We will use one for BUY side and one for SELL side.

We will also keep track of active IDs using an unordered map, with the key being the ID and value being the price and side (BUY/SELL).

OrderBook will be implemented as a class, with private members being buyOrders, sellOrders and active IDs. Public members being methods like adding or cancelling an order.

Methods for the class include addOrder and cancelOrder, which will both be void.