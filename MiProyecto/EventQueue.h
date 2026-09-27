#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

enum EventType {
	EV_HALF_POINTS,
	EV_END_HALF_POINTS,
	EV_SPEED_UP,
	EV_END_SPEED_UP,
	EV_DOUBLE_POINTS,
	EV_END_DOUBLE_POINTS
};

class EventNode {
public:
	EventType type;
	int priority; 
	EventNode* next;

	EventNode(EventType t, int p);
};

class EventQueue {
private:
	EventNode* head;
	
public:
	EventQueue();
	~EventQueue();
	void scheduleEvent(EventType type, int priority);
	bool hasReadyEvent(int currentPriority);
	EventType popEvent();
	void clear();
};

#endif
