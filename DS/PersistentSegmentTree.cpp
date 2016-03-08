class PersistentSegmentTree {

public:

  typedef int NodeType;             // data which is stored in segment tree
                                    // for segment tree of addition, it's just sum
                                    // so int. for segment tree storing multiple 
                                    // information, we can have a struct having required fields
                                    // the struct should just have a + operator which is used for merging.

  typedef int UpdateType;           // updateType 

  static NodeType merge(NodeType A, NodeType B) {
    return A + B;
  }

  static NodeType updateAns(NodeType Prev, NodeType Upd) {
    return Upd + Prev;
  }

  struct node {
    NodeType sum;
    node * left, * right;
    node(NodeType sum) : sum(sum) {
      left = right = NULL;
    }
    node(node * left, node * right) : left(left), right(right) {
      sum = merge(left->sum, right->sum);
    }
  };

  node * root[100001];  // stores pointers to head of all trees.
  int n;                // total nodes in tree.
  int numberOfTrees;    // total number of trees, more like how many updates have been there.

  PersistentSegmentTree(int n) : n(n) {
    root[0] = build(0, n - 1);          // build the initial tree.
    numberOfTrees = 1;                  // initiall number of tree are 1.
  }

  int update(int treeId, int index, UpdateType value, bool createNew) {

    // Arguments:
    // treeId: which version of tree to update.
    // index: which index to update in tree.
    // value : updateValue
    // createNew : whether to create new tree or not.
    //              if it's set, new tree version id gets alloted and new tree is created.
    //              if not the treeId given is updated.

    // Returns : Returns the tree just formed, or updated.

    if(!createNew) { updateNoSpace(root[treeId], 0, n - 1, index, value); return treeId; }
    else { root[numberOfTrees++] = update(root[treeId], 0, n - 1, index, value); return numberOfTrees - 1; }
  }

  NodeType query(int treeId, int start, int end) {
    /*
        Arguments :
            treeId : tree to query on.
            start : range start
            end : range end
        Returns :
            NodeType after querying in the given range in the given tree.
    */

    return query(root[treeId], 0, n - 1, start, end);
  }

private:

  NodeType leafNode(int index) {
    /* leafNode : Returns the value of node initially at an index.
                  used in build function.
    */
    return 0;
  }

  NodeType NodeTypeOutOfRange() {
    return 0;
  }

  node * update(node * head, int start, int end, int index, UpdateType value) {
    if(index < start || index > end) return head;         // dont need to update node not in range.
    if(start == end) return new node(updateAns(head->sum, value));
    int mid = (start + end) >> 1;
    return new node(update(head->left, start, mid, index, value), update(head->right, mid + 1, end, index, value));
  }

  void updateNoSpace(node * & head, int start, int end, int index, UpdateType value) {
    if(index < start || index > end) return;
    if(start == end) { head->sum = updateAns(head->sum, value); return; }
    int mid = (start + end) >> 1;
    updateNoSpace(head->left, start, mid, index, value), updateNoSpace(head->right, mid + 1, end, index, value);
    head->sum = merge(head->left->sum, head->right->sum);
  }

  NodeType query(node * head, int start, int end, int rs, int re) {
    if(rs > end || start > re) return NodeTypeOutOfRange();
    if(start >= rs && end <= re) return head->sum;
    int mid = (start + end) >> 1;
    return merge(query(head->left, start, mid, rs, re), query(head->right, mid + 1, end, rs, re));
  }  

  node * build(int start, int end) {
    if(start == end) return new node(leafNode(start));
    else {
      int mid = (start + end) >> 1;
      return new node(build(start, mid), build(mid + 1, end));
    }
  }

};
