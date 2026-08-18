## Phases
M1 - Specification & Setup

M2 - Order Book

M3 - Matching Engine

M4 - Cancellation & CLI

M5 - Testing & Polish

## Specification & Setup
The purpose is to define behavior before coding.
Think through:

What is an order?

When do buy/sell orders match?

What gets priority?

What happens with partial fills?

What happens to unmatched quantity?

What is invalid input?

How should cancellation behave?

What is explicitly out of scope?

include/

Public interfaces — what the classes allow you to do.

src/

Implementation — how those operations work.

CMakeLists.txt

Describes how to build the program.

CMakeLists.txt
      ↓

generates build system
      ↓

Make / Ninja / etc.
      ↓

compiler

Using C++17 compiler. 
g++ and clang++ are commands used to compile C++ source code into programs the computer can run.

g++ = the C++ compiler command from GCC (GNU Compiler Collection)

clang++ = the C++ compiler command from Clang/LLVM

clang++ -std=c++17 main.cpp -o app

This means: Compile main.cpp as C++17 and create an executable named app.

## What am I building?
The point of the project is to simulate the core mechanism of trading/exchange on apps like Robinhood, etc.

Buy/Sell Orders
      ↓
   Order Book
      ↓
Matching Engine
      ↓
    Trades

It has two main components: the limit order book and the matching engine.

## An Order
An order is simply a request to buy or sell something.

An example of this could be: Buy 10 shares of XYZ at $100 or cheaper.

The "Order" could be an object with fields such as:
Order ID: 123
Side: BUY
Price: $100
Quantity: 10

Someone else could say: Sell 5 shares of XYZ for $101 or higher.

That order could look like:
Order ID: 456
Side: SELL
Price: $101
Quantity: 5

On the buy side, this means the person is willing to pay up to $100 for a share, so <= $100.

On the sell side, the person is willing to sell their share for no less than $101, so >= $101.

These two people cannot trade because there's no overlap:
Buyer:  max $100
Seller: min $101

It's called a limit order because there's a limit on the priec you are willing to accept for both the buyer and seller.

An order is someone's request to buy or sell a certain quantity, with a limit on the price they're willing to accept.


## The Order Book
The order book is a queue for orders that have not traded yet.

It keeps two separate lists:
Buy orders → called bids
Sell orders → called asks

Take these orders for example:
BUYERS
Buy 10 @ $100
Buy  5 @ $99
Buy 20 @ $97

SELLERS
Sell 8 @ $103
Sell 4 @ $105
Sell 7 @ $108

The order book organizes them like this:
SELLS (asks)

$108   7 shares
$105   4 shares
$103   8 shares   ← cheapest seller

-----------------

$100  10 shares   ← highest-paying buyer
$99    5 shares
$97   20 shares

BUYS (bids)

They are organized this way because the most important orders are the ones closest to trading.

For buyers, the most competitive buyer is the one offering the highest price:
$100 > $99 > $97

For sellers, the most competitive seller is asking for the lowest price:
$103 < $105 < $108

Best bid = highest buy price
Best ask = lowest sell price

So, $103 is the best ask, while $100 is the best bid. 

The buyer refuses to pay more than $100.
The seller refuses to accept less than $103.

$100 < $103

No trade is possible

Those orders sit in the order book and wait.

At a later time, a buyer could come along and bid $104, while someone is willing to sell for $103. 

This is where the matching engine comes in.

If multiple people want the same price:
10:00 AM → Alice: BUY 5 @ $100
10:01 AM → Bob:   BUY 8 @ $100
10:03 AM → Chris: BUY 3 @ $100

The order book still needs to remember who arrived first:
$100:
Alice → Bob → Chris

If someone sells into those buyers, Alice should normally get her chance first because she placed her order first.

That's the time part of price-time priority:
Better price wins first.
If prices are equal, earlier order wins first.

So price first, time second as a tiebreaker. 

The order book can quickly look at the best available buyer and seller and determine whether a trade is possible.

Order = one person's request.

Order book = the organized waiting list containing everybody's unfilled requests.

I was deciding using a queue as the data structure. This would slightly inefficient because every time we add an order, we would have to sort the queue by price and time. I was also thinking about using a heap. It would be easy to retrieve the best order but accessing/removing orders from the middle would get messy.

Finally, I decided on using a map with the key being that particular price point and the value being a deque of orders. This preserves the best price ordering, and the FIFO property needed. I also could have used a queue or vector as the key. The problem with a queue is that we can only access the front and back of the queue. So, if an order is cancelled, then we can't iterate through the queue and remove the order. We would have to pop each order if it's order ID doesn't match the cancelled order and add it to a temporary queue. We can iterate through a vector and it has efficient push front, push back, front access and back access operations. The problem is, if we need to remove an element from the middle, we woulc have to shift everything left, which would be inefficient.

We will also keep track of the IDs using an unordered_map, with the key being the ID and the value being the price and the side. I was deciding between using a set, map and unordered_map. At first, I was thinking that maybe we don't need a key-value pair since we are just keeping track of IDs, but then I realized that keeping track of the price and the side will make cancellation more efficient because we can jump directly to the correct map and price. I decided to use an unordered map over a map because sorted order for cheking exisitng IDs isn't necessary.

OrderBook should be a class because it owns related data (buyOrders, sellOrders, activeIDs) and the operations that act on that data, such as adding and cancelling orders.

buyOrders, sellOrders and activeIDs will all be private because we don't want something like: buyOrders.clear(); it has to go through methods you control, like:
book.cancelOrder("A123");

That way, OrderBook can make sure all related state stays consistent, including the price maps and activeIDs.
Private protects the book from being changed incorrectly from the outside.

This concept is called encapsulation.
In simple terms, encapsulation means:
Keep an object's internal data protected, and only allow controlled access through its public methods.

So in your OrderBook:
private data structures = hidden internal state
public methods like addOrder() or cancelOrder() = controlled ways to change that state.

## The Matching Engine
The matching engine looks at incoming orders and decides whether they can trade with orders already waiting in the order book.

It asks if this new order trade with someone already waiting.

If yes, it creates a trade. If not, the new order gets added to the order book.

For example, suppose the order book currently has:
Best seller:
SELL 5 @ $100

Then a new order arrives:
BUY 3 @ $102

The buyer is willing to pay up to $102.
The seller is willing to sell for $100.

There is overlap, so a trade is possible.

buyer max = $102
seller min = $100

A trade happens for 3 shares (min(buyer shares, seller shares)).

Afterward:
BUY 3 @ $102   → completely filled

SELL 5 @ $100
          ↓
SELL 2 @ $100  → still waiting

The seller had 5 shares but only 3 were bought, so 2 remain.
That's called a partial fill.

Filled means that some or all of an order has successfully traded.

If you wanted to buy 10 shares and all 10 traded, then the order is fully filled.

If only 4 traded, then it's partially filled, and you still have 6 remaining.

What if one big order can match several orders?

Suppose the sellers are:
SELL 3 @ $100
SELL 4 @ $101
SELL 5 @ $102

Then someone submits:
BUY 10 @ $102

The buyer is willing to pay up to $102.
The engine starts with the best seller:
SELL 3 @ $100

Buy all 3.
Buyer still needs 7 more shares.

Then:
SELL 4 @ $101

Buy all 4.
Buyer still needs 3 more shares.

Then:
SELL 5 @ $102

Only 3 more are needed, so 3 trade.

Final result:
SELL 3 @ $100 → filled
SELL 4 @ $101 → filled
SELL 5 @ $102 → 2 remaining

BUY 10 @ $102 → filled
So one incoming order can cause multiple trades.

What if the prices don't work?
Suppose the best seller wants:
SELL @ $105

and the new buyer says:
BUY @ $102

The buyer refuses to pay more than $102.

So:
$102 < $105

No trade.
The matching engine stops and puts the buyer into the order book to wait.

The basic algorithm:
For a new buy order, look at the cheapest/most competitive seller.
If there's an overlap (Is seller's price <= buyer's limit?): a trade can happen.
If a trade can happen: take the minimum of the buy shares and sell shares, and subtract that amount from both.
If a trade cannot happen: stop and store the buyer in the order book queue.

For a new seller, look at the most expensive/most competitve buyer.
If there's an overlap (Is buyer's price >= seller's limit?): a trade can happen.
If a trade can happen: take the minimum of the buy shares and sell shares, and subtract that amount from both.
If a trade cannot happen: stop and store seller in the order book queue.

This keeps repeating until either:
the new order is completely filled, or
there are no more compatible orders.

The order book and matching engine have different jobs.

Order book keeps track of who is currently waiting.

Matching engine decides who should trade right now.

New order
   ↓
Matching Engine
   ↓
Check Order Book
   ↓
Trade if possible
   ↓
Put leftover order in book


## Price-Time Priority
Price-time priority is the rule for deciding who gets served first, if there are multiple orders.

Better price goes first

Suppose buyers are waiting:
BUY 5 @ $100
BUY 5 @ $102
BUY 5 @ $101

A seller arrives.

The buyer offering $102 gets priority because that's the best price for the seller.

So the order is:
$102 first
$101 second
$100 third

For sellers, it works the opposite way.

Suppose:
SELL 5 @ $105
SELL 5 @ $103
SELL 5 @ $104

A buyer arrives.

The seller asking for $103 goes first because that is the cheapest seller.
So:
$103 first
$104 second
$105 third

That's the price part.

If the prices are equal, earlier order goes first.

Suppose three buyers all want the same price:
10:00 AM → Alice: BUY 5 @ $100
10:01 AM → Bob:   BUY 5 @ $100
10:02 AM → Chris: BUY 5 @ $100

Since the price is identical, price cannot decide.

So we use arrival time:
Alice first
Bob second
Chris third

The rule is:
Best price first. If the price is tied, oldest order first.