#include "iostream"
#include "vector"
#include "list"
using namespace std;
struct Node {
	string data;
	string value;
	Node* right;
	Node* left;
	~Node() {
		if (right != NULL)
			delete right;
		if (left != NULL)
			delete left;
	}
};

typedef struct Node* NODE;

class BinaryStringTree
{
public:
	BinaryStringTree();
	~BinaryStringTree();
private:
	NODE m_head = NULL;
	NODE createNode(string data);
	NODE createNodeEx(string data, string value);
	string localinOrderTraversal(Node* node);
	string localinOrderTraversalEx(Node* node);
	vector<NODE> flatNode();
	NODE LinkNode(vector<NODE> flatOrderNode, int from, int to, bool bLeft);

public:
	Node* getHead()
	{
		return m_head;
	}
	void setHead(Node* head)
	{
		m_head = head;
	}
	void insertNode(string data);
	void insertNodeEx(string data, string value);
	Node* FindNode(string data);
	string inOrderTraversal();
	string inOrderTraversalEx();
	void BalanceTree();
};

BinaryStringTree::BinaryStringTree()
{

}
BinaryStringTree::~BinaryStringTree()
{
	if (m_head == NULL)
		delete m_head;
}

NODE BinaryStringTree::createNode(string data) {
	NODE newNode = new Node();

	if (!newNode) {
		cout << "Not enough memory" << endl;
		exit(-1);
	}
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->data = data;
	return (newNode);
}

NODE BinaryStringTree::createNodeEx(string data, string value) {
	NODE newNode = new Node();

	if (!newNode) {
		cout << "Not enough memory" << endl;
		exit(-1);
	}
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->data = data;
	newNode->value = value;
	return (newNode);
}

void BinaryStringTree::insertNode(string data) {

	NODE newNode = createNode(data);
	NODE hold_the_head = m_head;
	if (m_head == NULL) {
		m_head = newNode;
		m_head->right = NULL;
		m_head->left = NULL;
		return;
	}

	while (1) {
		if ((newNode->data > m_head->data) && (m_head->right == NULL)) {
			m_head->right = newNode;
			m_head = hold_the_head;
			return;
		}
		else if (newNode->data > m_head->data) {
			m_head = m_head->right;
		}

		else if ((newNode->data < m_head->data) && (m_head->left == NULL)) {
			m_head->left = newNode;
			m_head = hold_the_head;
			return;
		}
		else if (newNode->data < m_head->data) {
			m_head = m_head->left;
		}
		else // equals
		{
			m_head = hold_the_head;
			delete newNode;
			return;
		}
	}
}

void BinaryStringTree::insertNodeEx(string data, string value) {

	NODE newNode = createNodeEx(data, value);
	NODE hold_the_head = m_head;
	if (m_head == NULL) {
		m_head = newNode;
		m_head->right = NULL;
		m_head->left = NULL;
		return;
	}

	while (1) {
		if ((newNode->data > m_head->data) && (m_head->right == NULL)) {
			m_head->right = newNode;
			m_head = hold_the_head;
			return;
		}
		else if (newNode->data > m_head->data) {
			m_head = m_head->right;
		}

		else if ((newNode->data < m_head->data) && (m_head->left == NULL)) {
			m_head->left = newNode;
			m_head = hold_the_head;
			return;
		}
		else if (newNode->data < m_head->data) {
			m_head = m_head->left;
		}
		else // equals
		{
			m_head = hold_the_head;
			delete newNode;
			return;
		}
	}
}

NODE BinaryStringTree::FindNode(string data)
{
	NODE itorNode = m_head;
	if (itorNode == NULL) {
		return NULL;
	}

	while (1) {
		if ((data > itorNode->data) && (itorNode->right == NULL)) {
			return NULL;
		}
		else if (data > itorNode->data) {
			itorNode = itorNode->right;
		}

		else if ((data < itorNode->data) && (itorNode->left == NULL)) {
			return NULL;
		}
		else if (data < itorNode->data) {
			itorNode = itorNode->left;
		}
		else // equals
		{
			return itorNode;
		}
	}
}

string BinaryStringTree::inOrderTraversal()
{
	string data = "";
	if (m_head == NULL)
		return data;
	data += localinOrderTraversal(m_head->left);
	data += m_head->data + "\n";
	data += localinOrderTraversal(m_head->right);
	return data;
}

string BinaryStringTree::inOrderTraversalEx()
{
	string data = "";
	if (m_head == NULL)
		return data;
	data += localinOrderTraversalEx(m_head->left);
	data += m_head->data + "," + m_head->value + "\n";
	data += localinOrderTraversalEx(m_head->right);
	return data;
}

string BinaryStringTree::localinOrderTraversal(Node* node) {
	string data = "";
	if (node == NULL)
		return data;
	data += localinOrderTraversal(node->left);
	data += node->data + "\n";
	data += localinOrderTraversal(node->right);
	return data;
}

string BinaryStringTree::localinOrderTraversalEx(Node* node) {
	string data = "";
	if (node == NULL)
		return data;
	data += localinOrderTraversalEx(node->left);
	data += node->data + "," + node->value  + "\n";
	data += localinOrderTraversalEx(node->right);
	return data;
}

vector<NODE> BinaryStringTree::flatNode()
{
	list<NODE> dataTemp;
	vector<NODE> out;
	Node* head = getHead();

	if (head == NULL)
		return out;

	dataTemp.push_back(head->right);
	dataTemp.push_back(head);
	dataTemp.push_back(head->left);

	while (dataTemp.size())
	{
		Node* re = dataTemp.back();
		dataTemp.pop_back();
		if (re == NULL)
		{	
			if (dataTemp.size() > 0)
			{
				out.push_back(dataTemp.back());
				dataTemp.pop_back();
			}
		}
		else
		{
			dataTemp.push_back(re->right);
			dataTemp.push_back(re);
			dataTemp.push_back(re->left);
		}
	}
	return out;
}

NODE BinaryStringTree::LinkNode(vector<NODE> flatOrderNode, int from, int to, bool bLeft)
{
	if (bLeft && (from == to))
	{
		return NULL;
	}
	else if (bLeft && (from + 1 == to) && from != 0)
	{
		return NULL;
	}

	if (!bLeft && (from == to))
	{
		return NULL;
	}
	else if (!bLeft && (from + 1 == to) && to != flatOrderNode.size() - 1)
	{
		return NULL;
	}

	int mid = 0;
	if (bLeft)
	{
		mid = from + (to - from) / 2;
	}
	else 
	{
		int add = (to - from) % 2;
		mid = from + (to - from) / 2 + add;
	}

	NODE NodeSet = flatOrderNode[mid];
	NODE left = LinkNode(flatOrderNode, from, mid, true);
	NODE right = LinkNode(flatOrderNode, mid, to, false);

	NodeSet->left = left;
	NodeSet->right = right;
	return NodeSet;
}

void BinaryStringTree::BalanceTree()
{
	vector<NODE> flatOrderNode = flatNode();
	NODE head = LinkNode(flatOrderNode, 0, flatOrderNode.size() - 1, true);
	setHead(head);
}

int main() {

	BinaryStringTree tree;
	tree.insertNode("karan");
	tree.insertNode("sameer");
	tree.insertNode("palak");
	tree.insertNode("jagdish");
	tree.insertNode("naman");
	tree.insertNode("umang");
	tree.insertNode("chandu");
	tree.insertNode("demo");

	NODE dataNode = tree.FindNode("chandu");
	string data = tree.inOrderTraversal();
	tree.BalanceTree();
	NODE dataNode2 = tree.FindNode("abc");
	cout << data.c_str() << endl;
	return 0;
}