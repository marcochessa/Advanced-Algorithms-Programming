### Laboratory Exercise No. 11

#### Exercise 1: Stock Quotes

**Extended Version of the Exam Assignment from 13/09/2018**

Stock shares of publicly traded companies can be transacted (buying/selling a certain number of shares at a certain date/time at a certain value on a certain exchange) on one or more financial exchanges worldwide. Imagine creating a global system that considers all exchanges for storing and managing stock shares.

Each exchange regularly sends a file to the system with a list of transactions grouped by stock. The file format is as follows:
- The first line contains the number of stocks, followed by the stocks and their respective transactions in the following format:
  - **A line containing the <stock>** (a unique alphanumeric code of up to 20 characters) followed by the number of transactions.
  - **Subsequent lines**, one per line, list the transactions in the form of a quadruple: `<date> <time> <value> <quantity>`. Dates are in the format yyyy/mm/dd, times are in 24-hour format hh:mm referring to Greenwich Mean Time (GMT), while stock values are represented by non-negative real numbers and quantity is an integer.
  - **No assumption of sorting** is made regarding stock names or transactions.

The system should acquire the files and store their contents in a suitable two-level data structure that includes a collection of stocks, and for each stock, a collection of its daily quotes. The daily quote \( Q_i \) for a stock on a specific date \( i \) is the average of all values \( v_{ij} \) of that stock on that date \( i \) weighted by the number of shares traded \( n_{ij} \):
\[ Q_i = \frac{\sum (v_{ij} \cdot n_{ij})_j}{\sum n_{ij}_j} \]

**Requirements:**
1. Implement a quasi ADT for the date, using a struct with integer fields for year, month, and day.
2. Implement a Class I ADT for the stock and one for the collection of stocks (either in one module or two). Use a sorted list for the stock collection.
3. Implement a quasi ADT for the daily quote and a Class I ADT for the collection of daily quotes (either in one module or two). Use a Binary Search Tree (BST) for the collection of quotes.
4. Implement a client that provides the following functionalities:
   1. Acquisition of the contents of a file containing a set of transactions.
   2. Search for a stock.
   3. Given a previously selected stock, search for its quote on a specific date.
   4. Given a previously selected stock, search for its minimum and maximum quote within a specific date range.
   5. Given a previously selected stock, search for its minimum and maximum quote over the entire recorded period.
   6. Given a previously selected stock, balance the BST of quotes if the ratio between the longest and shortest path in the tree exceeds a certain threshold \( S \). Note: Balancing a BST can be achieved through recursive partitioning based on the median key.