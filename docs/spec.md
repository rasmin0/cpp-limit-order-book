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

Unmatched orders means that the seller's asking price is higher than the bid, so no trade happens; everything is left unchanged.

If there's a cancellation, the order is removed from the queue.

