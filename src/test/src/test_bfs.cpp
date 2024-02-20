#include <iostream>
#include <queue>
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

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        // 当前层的节点数量
        int levelSize = q.size();
        while (levelSize--) {
            // 弹出队首节点并访问它
            TreeNode* node = q.front();
            cout << node->val << " ";
            q.pop();

            // 将其左右子节点加入队列（如果存在）
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        // 输出换行符以区分不同层次
        cout << endl;
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