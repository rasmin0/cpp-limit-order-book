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


