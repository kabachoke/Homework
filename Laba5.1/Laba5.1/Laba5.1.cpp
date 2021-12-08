#include "Header.hpp"

std::string FILE_NAME = "result.txt";

class ClientInfo
{
public:
	int sberbook_number;
	std::string name;
	int birthday_year;
	int deposit;
	int eblan_field;
	int consumption;
	int total = 0;
	ClientInfo(int s_n, std::string n, int b_y, int d, int e_f, int c)
		: sberbook_number(s_n), name(n), birthday_year(b_y), deposit(d), eblan_field(e_f), consumption(c), total(0) {}

	friend bool compare_clients(ClientInfo ci1, ClientInfo ci2);
};
bool compare_clients(ClientInfo ci1, ClientInfo ci2)
{
	for (int i = 0; i < ci1.name.length(); i++)
	{
		if (ci1.name[i] < ci2.name[i])
			return true;
		else if (ci1.name[i] == ci2.name[i])
			continue;
		else
			return false;
	}
	return false;
}
std::vector<std::string> split(std::string s, std::string del = " ")
{
	std::vector<std::string> result;
	int start = 0;
	int end = s.find(del);
	while (end != -1) {
		result.push_back(s.substr(start, end - start));
		start = end + del.size();
		end = s.find(del, start);
	}
	result.push_back(s.substr(start, end - start));

	return result;
}
ClientInfo parse_info(std::string content)
{
	std::vector<std::string> res = split(content, "\n");
	ClientInfo client(std::stoi(res[0]), res[1], std::stoi(res[2]),
		std::stoi(res[3]), std::stoi(res[4]), std::stoi(res[5]));
	return client;
}
std::vector<ClientInfo> deserialize(std::string content)
{
	std::vector<std::string> parse_result = split(content, "\n\n");
	std::vector<ClientInfo> clients;

	for (std::string str : parse_result)
		clients.push_back(parse_info(str));

	return clients;
	
}
std::string serialize(std::vector<ClientInfo> clients)
{
	std::string result = "";

	for (ClientInfo client : clients)
	{
		result += std::to_string(client.sberbook_number) + '\n';
		result += client.name + '\n';
		result += std::to_string(client.birthday_year) + '\n';
		result += std::to_string(client.deposit) + '\n';
		result += std::to_string(client.eblan_field) + '\n';
		result += std::to_string(client.consumption) + '\n';
		result += "Total:" + std::to_string(client.total) + "\n\n";
	}
	return result;
}
std::vector<ClientInfo> process(std::vector<ClientInfo> clients)
{
	int count_client_withdraw = 0, count_client_deposit = 0;

	std::sort(clients.begin(), clients.end(), compare_clients);

	for (int i = 0; i < clients.size(); i++)
	{
		clients[i].total = clients[i].deposit - clients[i].consumption;
		if (clients[i].eblan_field == 0)
			count_client_withdraw++;
		else
			count_client_deposit++;
	}
	
	printf("Count of clients, that deposit money: %d\n", count_client_deposit);
	printf("Count of clients, that withdraw money: %d\n", count_client_withdraw);

	return clients;
}
void write_file(std::string src)
{
	std::ofstream ofs(FILE_NAME);
	ofs << src;
	ofs.close();
}
int main()
{
	convert_to_bin();
	std::string content = convert_from_bin();

	std::vector<ClientInfo> clients = deserialize(content);
	clients = process(clients);
	std::string res = serialize(clients);

	write_file(res);

	return 0;
}
