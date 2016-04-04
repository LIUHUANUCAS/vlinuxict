#include<iostream>
#include<vector>
using namespace std;

class HasPtr{
	public:
		HasPtr(int *p,int i):ptr(p),val(i){}
		int* get_ptr()const{
			return ptr;
		}
		int get_val()const {
			return val;
		}
		void set_ptr(int *p){
			ptr = p;

		}
		void set_val(int i){
			val = i;

		}
		int get_ptr_val()const{
			return *ptr;
		}
		void set_ptr_val(int val)const {
			*ptr = val;
		}
	private:
		int *ptr;
		int val;

};
class Circle{
	public:
		Circle();
		Circle(double r);
		void print();
		~Circle();
	private:
		static int num;
		double radiu;
};
Circle::Circle():radiu(1.0){
	cout<<"circle const ..."<<endl;
	num++;
}
Circle::Circle(double r):radiu(r){
	num++;
}
Circle::~Circle(){
	num--;
}
void Circle::print(){
	cout<<"hello circle"<<endl;
	cout<<num<<endl;
}
int Circle::num = 0;
class Account{
	private :
		string owner;
		double amount;
		static double interestRate;
		static double initRate(){
			interestRate=0.1;
			return interestRate;
		}
	public:
		Account():amount(0.6){

		}
		void applyint(){
			amount += amount*interestRate;
		}
		static double rate(){return interestRate;}

};
double Account::interestRate;
class Order{
	private :
		int second,first;
	public:
		Order(int i,int j):second(j),first(i){
			//first=100;
			cout<<"first="<<first<<" second="<<second<<endl;
		}
		Order(int i):second(i++),first(++i){
			cout<<"first="<<first<<" second="<<second<<endl;
		}
};
class Page{
	private :
		int page;
		int width;
		int heigth;
	public:
		//explicit Page(int p):page(p),width(0),heigth(0){
		Page(int p):page(p),width(0),heigth(0){
		}
		Page(int p,int w,int h):page(p),width(w),heigth(h)
		{}
		void print(){
			cout<<"page="<<page<<" width="<<width<<" heigth="<<heigth<<endl;
		}
		int same_page(Page p ){
			cout<<"p.page= "<<p.page<<endl;
			return page==p.page;
		}
		int same_page(int p ){
			cout<<"p= "<<p<<endl;
			return page==p;
		}
};

class Book{
	public:
	Book(int n,const string &bname):
		num(n),name(bname)
	{
		num=100;
	}
	void print(){
		cout<<"n="<<num<<" -> name="<<name<<endl; 
	}
	private:
		int num;
		string name;
};
class Sales_Items{
	private :
		Book book;
		int times;
		Page page;
	public:
		Sales_Items(const Book& b,int t):book(b),times(t),page(1,2,3){
		
		}
		void print(){
			cout<<"=========================="<<endl;
			book.print();
			page.print();
			cout<<"times="<<times<<endl;
			cout<<"=========================="<<endl;
		}
};
class CopyName{
	public:
		CopyName():pstring(new string),i(0),d(0){}
		CopyName(const CopyName& name):pstring(new string(*name.pstring)),i(name.i),d(name.d){}
		void print(){
			cout<<pstring<<" i="<<i<<" d="<<d<<endl;
		}
		void setpstring(string& str){
			pstring = new string(str);
		}
		CopyName& operator=(const CopyName& name){
			i=name.i;
			d=name.d;
			pstring = new string(*name.pstring);
			this->print();
			return *this;
		}
		~CopyName(){
			delete pstring;
			cout<<"destroyed.."<<endl;
		}
	private:
		string *pstring;
		int i;
		double d;
};
int main(){
	Circle c[1];
	c[0].print();
	vector<Circle> cvec;
	cvec.push_back(c[0]);

	int *ip = new int(32);
	HasPtr ptr1(ip,10);
	ptr1.set_ptr_val(11);

	cout<<"-------------"<<endl;
	HasPtr p2 = ptr1;
	cout<<p2.get_ptr_val()<<endl;
	ptr1.set_ptr_val(200);
	cout<<ptr1.get_ptr_val()<<endl;
	cout<<p2.get_ptr_val()<<endl;


	return 0;
}
int main2(){
	CopyName cname;
	string hello = "hello";
	//cname.setpstring(hello);
	cname.print();
	CopyName ccname(cname);
	ccname.print();
	CopyName cname2 = cname;
	cname2.print();
	string name="c++primer";
	Book b(1,name);
	b.print();
	Sales_Items sales_item(b,2);
	sales_item.print();
	Order order(1,2);
	Order ord(12);
	Page page(200,2,3);
	cout<<page.same_page(200)<<endl;
	Account acount = Account();
	
	cout<<acount.rate()<<endl;
	cout<<Account::rate()<<endl;
	acount.applyint();
	
	Circle c;
	c.print();

	
	return 0;
}
