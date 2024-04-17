#include <iostream>
#include <queue>
#include <stack>
#include "test/test.h"
using namespace std;

// 定义二叉树节点结构体
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 广度优先遍历函数
void bfsTraversal(TreeNode* root) {
    if (!root) return;

    queue<TreeNode*> container;
    container.push(root);

    while (!container.empty()) {
        // 当前层的节点数量
        int levelSize = container.size();
        while (levelSize--) {
            // 弹出队首节点并访问它
            TreeNode* node = container.front();
            cout << node->val << " ";
            container.pop();

            // 将其左右子节点加入队列（如果存在）
            if (node->left) container.push(node->left);
            if (node->right) container.push(node->right);
        }
        // 输出换行符以区分不同层次
        cout << endl;
    }
}
// 迭代先序遍历
void iterativePreorderTraversal(TreeNode* root) {
    if (root == nullptr) return;

    std::stack<TreeNode*> stack;
    stack.push(root);

    while (!stack.empty()) {
        TreeNode* node = stack.top();
        stack.pop();

        // 访问当前节点
        std::cout << node->val << " ";

        // 先将右子节点压入栈，再将左子节点压入栈，确保先访问左子节点
        if (node->right) stack.push(node->right);
        if (node->left) stack.push(node->left);
    }
}
// 迭代中序遍历
void iterativeInorderTraversal(TreeNode* root) {
    if (root == nullptr) return;

    std::stack<TreeNode*> stack;
    TreeNode* curr = root;

    while (curr != nullptr || !stack.empty()) {
        // 将所有左子节点入栈，直到找到最左侧节点（无左子节点）
        while (curr != nullptr) {
            stack.push(curr);
            curr = curr->left;
        }

        // 访问最左侧节点（无左子节点）
        if (!stack.empty()) {
            curr = stack.top();
            stack.pop();
            std::cout << curr->val << " ";
            curr = curr->right; // 移动到当前节点的右子节点
        }
    }
}
// 迭代后序遍历
void postorderTraversal(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    stack<TreeNode*> s1, s2;
    s1.push(root);
    while (!s1.empty()) {
        TreeNode* node = s1.top();
        s1.pop();
        s2.push(node);
        if (node->left != NULL) {
            s1.push(node->left);
        }
        if (node->right != NULL) {
            s1.push(node->right);
        }
    }

    while (!s2.empty()) {
        cout << s2.top()->val << " ";
        s2.pop();
    }
}
void test_bfs()
{
    // 构造一个简单的二叉树
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    // 执行广度优先遍历
    bfsTraversal(root);


}
