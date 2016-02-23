#pragma once

#include "Constants.h"

#include <unordered_set>

OFX_ANIMATION_PRIMITIVES_BEGIN_NAMESPACE

struct CommandQueueCommand;
struct JoinCommand;
struct UntilCommand;

struct Command {
	using Callback = std::function<void(float)>;
	static void Empty() {}
	static void EmptyUpdate(float) {}
	
	std::function<void(void)> start = Empty;
	std::function<void(float)> update = EmptyUpdate;
	std::function<void(void)> finish = Empty;
	
	bool is_async = false;
	
	virtual void reset() {}
	virtual bool updateTick(float tick) { return false; }
};

struct LinearCommand : public Command {
	float current = 0, duration;
	
	LinearCommand()
		: current(0)
		, duration(0)
	{}
	
	LinearCommand(float duration)
		: duration(duration)
	{}
	
	void reset() override {
		current = 0;
	}
	
	bool updateTick(float tick) override {
		float pct = current / duration;
		
		update(pct);
		
		current += tick;
		
		if (current > duration) {
			current = duration;
			return false;
		}
		
		return true;
	}
};

struct CallbackCommand : public Command {
	
	CallbackCommand(const std::function<void(void)>& fn)
		: fn(fn)
	{
		this->start = fn;
	}
	
	bool updateTick(float tick) override {
		return false;
	}
	
	std::function<void(void)> fn;
};

class CommandQueue
{
public:
	
	CommandQueue& then(const std::function<void(void)>& fn) {
		auto o = std::make_shared<CallbackCommand>(fn);
		queue.emplace_back(o);
		return *this;
	}

	CommandQueue& then(float duration, const std::function<void (float)>& update) {
		auto o = std::make_shared<LinearCommand>(duration);
		o->update = update;
		queue.emplace_back(o);
		return *this;
	}
	
	CommandQueue& then(CommandQueue& CQ) {
		auto o = std::make_shared<CommandQueueCommand>(&CQ);
		CQ.parent = this;
		sub_commnad_queues.insert(&CQ);
		queue.emplace_back(o);
		return *this;
	}

	template <typename T>
	CommandQueue& then(const std::function<void (T*)>& fn) {
		auto o = std::make_shared<LinearCommand>();
		fn(o.get());
		queue.emplace_back(o);
		return *this;
	}
	
	CommandQueue& async(float duration, const std::function<void(float)>& update, const std::function<void(void)>& finish = Command::Empty) {
		auto o = std::make_shared<LinearCommand>(duration);
		o->is_async = true;
		o->update = update;
		o->finish = finish;
		queue.emplace_back(o);
		return *this;
	}

	CommandQueue& join()
	{
		auto o = std::make_shared<JoinCommand>(this);
		queue.emplace_back(o);
		return *this;
	}

	CommandQueue& wait(float duration = std::numeric_limits<float>::infinity())
	{
		auto o = std::make_shared<LinearCommand>(duration);
		queue.emplace_back(o);
		return *this;
	}
	
	CommandQueue& until(const std::function<bool(float)>& update)
	{
		auto o = std::make_shared<UntilCommand>(update);
		queue.emplace_back(o);
		return *this;
	}
	
	void start()
	{
		reset();
		startFrontQueue();
	}
	
	void reset()
	{
		running_queue = queue;
	}
	
	void clear()
	{
		running_queue.clear();
		queue.clear();
	}
	
	void update(float tick)
	{
		// only root commandd queue
		if (this->parent == nullptr)
		{
			updateAsync(tick);
		}
		
		if (running_queue.empty()) return;
		
		if (running_queue.front()->updateTick(tick) == false)
		{
			next();
		}
	}
	
	void next()
	{
		if (running_queue.empty()) return;
		
		auto front = running_queue.front();
		front->update(1);
		front->finish();
		running_queue.pop_front();
		
		if (running_queue.empty()) return;
		
		startFrontQueue();
	}

	bool isFinished() const { return running_queue.size() == 0 && !queue.empty(); }
	bool hasAsyncCommands() const { return !async_commands.empty(); }
	
private:
	
	std::vector<std::shared_ptr<Command>> async_commands;
	std::deque<std::shared_ptr<Command>> running_queue;
	
	std::deque<std::shared_ptr<Command>> queue;
	
	CommandQueue* parent = nullptr;
	std::unordered_set<CommandQueue*> sub_commnad_queues;
	
	void startFrontQueue()
	{
		if (running_queue.empty()) return;
		
		while (!running_queue.empty())
		{
			auto front = running_queue.front();
			
			front->reset();
			front->start();
			
			// async command
			if (front->is_async)
			{
				async_commands.push_back(front);
				running_queue.pop_front();
				continue;
			}
			
			// callback only command
			if (front->updateTick(0) == false)
			{
				front->update(1);
				front->finish();
				running_queue.pop_front();
				continue;
			}
			
			break;
		}
	}
	
	void updateAsync(float tick)
	{
		auto it = async_commands.begin();
		while (it != async_commands.end())
		{
			auto ptr = it->get();
			if (ptr->updateTick(tick) == false)
			{
				ptr->update(1);
				ptr->finish();
				
				it = async_commands.erase(it);
			}
			else
				it++;
		}
		
		for (auto& it : sub_commnad_queues)
		{
			it->updateAsync(tick);
		}
	}
};

//

struct CommandQueueCommand : public Command {
	
	CommandQueueCommand(CommandQueue* CQ)
		: CQ(CQ)
	{
		this->start = [this]() {
			this->CQ->start();
		};
	}
	
	bool updateTick(float tick) override {
		CQ->update(tick);
		return !CQ->isFinished();
	}
	
	CommandQueue* CQ;
};

struct JoinCommand : public Command {
	
	JoinCommand(CommandQueue* CQ)
		: CQ(CQ)
	{}
	
	bool updateTick(float tick) override {
		return CQ->hasAsyncCommands();
	}
	
	CommandQueue* CQ;
};

struct UntilCommand : public Command {
	
	std::function<bool(float)> fn;
	float current = 0;
	
	UntilCommand(std::function<bool(float)> fn)
		: fn(fn)
	{}
	
	void reset() override {
		current = 0;
	}

	bool updateTick(float tick) override {
		current += tick;
		return fn(current);
	}
};

OFX_ANIMATION_PRIMITIVES_END_NAMESPACE
