//mulitiset
mulitiset<int>c;
c.size()     //返回当前的元素数量
c.empty ()   //判断大小是否为零，等同于0 == size()，效率更高
count (elem) //返回元素值为elem的个数
find(elem)   //返回元素值为elem的第一个元素，如果没有返回end()
lower _bound(elem)  //返回元素值为elem的第一个可安插位置，也就是元素值 >= elem的第一个元素位置
upper _bound (elem) //返回元素值为elem的最后一个可安插位置，也就是元素值 > elem 的第一个元素位置
c.begin()  //返回一个随机存取迭代器，指向第一个元素
c.end()    //返回一个随机存取迭代器，指向最后一个元素的下一个位置
c.rbegin() //返回一个逆向迭代器，指向逆向迭代的第一个元素
c.rend()   //返回一个逆向迭代器，指向逆向迭代的最后一个元素的下一个位置
c.insert(elem) //插入一个elem副本，返回新元素位置，无论插入成功与否。
c.insert(pos, elem) //安插一个elem元素副本，返回新元素位置，pos为收索起点，提升插入速度。
c.insert(beg,end) //将区间[beg,end)所有的元素安插到c，无返回值。
c.erase(elem) //删除与elem相等的所有元素，返回被移除的元素个数。
c.erase(pos) //移除迭代器pos所指位置元素，无返回值。
c.erase(beg,end) //移除区间[beg,end)所有元素，无返回值。
c.clear() //移除所有元素，将容器清空
//注意事项:mulitiset是在set的基础上允许重复元素，如果需要删除某个值x的其中一个元素，不能通过c.erase(3)，这样会删除所有值为3的元素
//而是it = c.find(3); c.erase(it);