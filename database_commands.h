#pragma once

#include <iostream>
#include <string>
#include <memory>
#include "database.h"
#include "node.h"


class DatabaseCmd
{
public:
	virtual void Exec(Database& db, std::ostream& os) const = 0;
	virtual void GetArgs(std::istream& is) {}
	virtual ~DatabaseCmd() {}
};


class AddCmd : public DatabaseCmd
{
public:
	void Exec(Database& db, std::ostream& os) const override;
	void GetArgs(std::istream& is) override;

private:
	Date d;
	std::string event;
};


class DeleteCmd : public DatabaseCmd
{
public:
	void Exec(Database& db, std::ostream& os) const override;
	void GetArgs(std::istream& is) override;

private:
	std::shared_ptr<Node> cond;
};


class FindCmd : public DatabaseCmd
{
public:
	void Exec(Database& db, std::ostream& os) const override;
	void GetArgs(std::istream& is) override;

private:
	std::shared_ptr<Node> cond;
};


class PrintCmd : public DatabaseCmd
{
public:
	void Exec(Database& db, std::ostream& os) const override
	{
		db.Print(os);
	}
};


class LastCmd : public DatabaseCmd
{
public:
	void Exec(Database& db, std::ostream& os) const override;
	void GetArgs(std::istream& is) override;

private:
	Date dt;
};


std::unique_ptr<DatabaseCmd> GetCmdByName(const std::string& cmdName);
void ProcessInput(Database& db, std::istream& is, std::ostream& os);
