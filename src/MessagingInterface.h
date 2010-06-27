#ifndef CLASS_MESSAGING_INTERFACE
#define CLASS_MESSAGING_INTERFACE

class MessagingInterface {
	public:
		virtual ~MessagingInterface();
		virtual void onMessage();
		
	protected:
		MessagingInterface();
		MessagingInterface(const MessagingInterface& M);
		 
	private:

};

#endif
