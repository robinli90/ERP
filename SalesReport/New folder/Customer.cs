using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ExcoUtility;

namespace SalesReport
{
    class Customer
    {
        // customer info
        ExcoCustomer customer;
        // amount
        public Plant mar = new Plant();
        public Plant mic = new Plant();
        public Plant tex = new Plant();
        public Plant col = new Plant();
        public Plant sum = new Plant();

        public Customer(ExcoCustomer customer)
        {
            this.customer = customer;
            mar.GetData(1, id, curr);
            mic.GetData(3, id, curr);
            tex.GetData(5, id, curr);
            col.GetData(4, id, curr);
            //sum = mar + mic + tex + col;
            sum.curr = curr;
        }

        public static Customer operator +(Customer a1, Customer a2)
        {
            string id = a1.id;
            if (a1.id.IndexOf('S') > 0)
            {
                id = a2.id;
            }
            Customer cust = new Customer(id, a1.name, a1.terr, a1.curr);
            if (0 != a1.name.CompareTo(a2.name))
            {
                throw new Exception("Customer names are different");
            }
            cust.mar = a1.mar + a2.mar;
            cust.mic = a1.mic + a2.mic;
            cust.tex = a1.tex + a2.tex;
            cust.col = a1.col + a2.col;
            cust.sum = a1.sum + a2.sum;
            return cust;
        }
    }
}
