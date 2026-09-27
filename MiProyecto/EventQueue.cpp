#include "EventQueue.h"

EventNode::EventNode(EventType t, int p) {
	this->type = t;
	this->priority = p;
	this->next = nullptr;
}

EventQueue::EventQueue() {
	head = nullptr;
}

EventQueue::~EventQueue() {
	clear();
}

void EventQueue::clear() {
	EventNode* temp = head;
	while (temp != nullptr) {
		EventNode* nextNode = temp->next;
		delete temp;
		temp = nextNode;
	}
	head = nullptr;
}

void EventQueue::scheduleEvent(EventType type, int priority) {
	EventNode* newNode = new EventNode(type, priority);
	if (head == nullptr || priority < head->priority) {
		newNode->next = head;
		head = newNode;
		return;
	}
	EventNode* current = head;
	while (current->next != nullptr && current->next->priority <= priority) {
		current = current->next;
	}	
	newNode->next = current->next;
	current->next = newNode;
}

bool EventQueue::hasReadyEvent(int currentPriority) {
	return head != nullptr && head->priority <= currentPriority;
}

EventType EventQueue::popEvent() {
	if (head == nullptr) return EV_HALF_POINTS; 	
	EventNode* temp = head;
	EventType type = temp->type;
	head = head->next;
	delete temp;	
	return type;
}
