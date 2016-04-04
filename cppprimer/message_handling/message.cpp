#include<iostream>
#include<set>
using namespace std;
class Message;
class Folder;
class Folder{
	public:
		Folder(const string& fname):folder_name(fname){}
//		Folder(const Folder& fold);
	//	Folder& operator=(const Folder & f);
		~Folder();
		void save(Message& msg);
		void remove(Message& msg);
		void addMsg(Message *m);
		void remMsg(Message *m);
	private:
		set<Message*> messages;
		string folder_name;
};
void Folder::addMsg(Message* m){
	messages.insert(m);
}
void Folder::remMsg(Message *m){
	messages.erase(m);
}
void Folder::save(Message& m){
	this->addMsg(&m);
}
void Folder::remove(Message& m){
	this->remMsg(&m);
}
class Message{
	public:
		Message(const string & str=""):contents(str){}
		Message(const Message & );
		Message& operator=(const Message &);
		~Message();
		void save(Folder&);
		void remove(Folder&);

	private:
		string contents;
		set<Folder*> folders;
		void put_Msg_in_Folders(const set<Folder*> &);
		void remove_Msg_from_Folders();
		void addFldr(Folder* folder);
		void remFldr(Folder* folder);
};
Message::Message(const Message& m):contents(m.contents),folders(m.folders){
	this->put_Msg_in_Folders(folders);
}
Message& Message::operator=(const Message& rhs){
	if(&rhs != this){
		this->remove_Msg_from_Folders();
		this->contents = rhs.contents;
		this->folders = rhs.folders;
		this->put_Msg_in_Folders(rhs.folders);
	}
	return *this;
}
void Message::save(Folder& folder){
	this->addFldr(&folder);
	folder.addMsg(this);
}
void Message::remove(Folder& folder){
	this->remFldr(&folder);
	folder.remMsg(this);
}
void Message::put_Msg_in_Folders(const set<Folder*> &rhs){
	for(set<Folder*>::const_iterator beg = rhs.begin();beg!=rhs.end();++beg){
		(*beg)->addMsg(this);
	}
}
void Message::remove_Msg_from_Folders(){
	for(set<Folder*>::const_iterator beg = folders.begin();beg!=folders.end();++beg){
		(*beg)->remMsg(this);
	}
}
void Message::addFldr(Folder* fold){
	folders.insert(fold);
}
void Message::remFldr(Folder* fold){
	folders.erase(fold);
}
Message::~Message(){
	this->remove_Msg_from_Folders();
}
int main(){

	return 0;	
}
