#include <vector>
#include <iostream>

// Representa um retângulo ou caixa delimitadora
struct AABB {
    float x, y, width, height;
    
    bool intersects(const AABB& other) const {
        return !(x + width < other.x || x > other.x + other.width ||
                 y + height < other.y || y > other.y + other.height);
    }
};

// Representa uma entidade do jogo
struct Entity {
    AABB bounds;
    // Outros dados da entidade
};

// Quadtree Node
class Quadtree {
    static const int MAX_ENTITIES = 4;
    static const int MAX_LEVELS = 5;

    int level;
    std::vector<Entity> entities;
    AABB bounds;
    Quadtree* nodes[4];

public:
    Quadtree(int pLevel, AABB pBounds) : level(pLevel), bounds(pBounds) {
        for (int i = 0; i < 4; i++) {
            nodes[i] = nullptr;
        }
    }

    ~Quadtree() {
        for (int i = 0; i < 4; i++) {
            delete nodes[i];
        }
    }

    void clear() {
        entities.clear();
        for (int i = 0; i < 4; i++) {
            if (nodes[i] != nullptr) {
                nodes[i]->clear();
                delete nodes[i];
                nodes[i] = nullptr;
            }
        }
    }

    void split() {
        float subWidth = bounds.width / 2;
        float subHeight = bounds.height / 2;
        float x = bounds.x;
        float y = bounds.y;

        nodes[0] = new Quadtree(level + 1, {x + subWidth, y, subWidth, subHeight});
        nodes[1] = new Quadtree(level + 1, {x, y, subWidth, subHeight});
        nodes[2] = new Quadtree(level + 1, {x, y + subHeight, subWidth, subHeight});
        nodes[3] = new Quadtree(level + 1, {x + subWidth, y + subHeight, subWidth, subHeight});
    }

    int getIndex(const AABB& pRect) const {
        int index = -1;
        float verticalMidpoint = bounds.x + (bounds.width / 2);
        float horizontalMidpoint = bounds.y + (bounds.height / 2);

        bool topQuadrant = (pRect.y < horizontalMidpoint && pRect.y + pRect.height < horizontalMidpoint);
        bool bottomQuadrant = (pRect.y > horizontalMidpoint);

        if (pRect.x < verticalMidpoint && pRect.x + pRect.width < verticalMidpoint) {
            if (topQuadrant) {
                index = 1;
            } else if (bottomQuadrant) {
                index = 2;
            }
        } else if (pRect.x > verticalMidpoint) {
            if (topQuadrant) {
                index = 0;
            } else if (bottomQuadrant) {
                index = 3;
            }
        }

        return index;
    }

    void insert(Entity entity) {
        if (nodes[0] != nullptr) {
            int index = getIndex(entity.bounds);

            if (index != -1) {
                nodes[index]->insert(entity);
                return;
            }
        }

        entities.push_back(entity);

        if (entities.size() > MAX_ENTITIES && level < MAX_LEVELS) {
            if (nodes[0] == nullptr) {
                split();
            }

            int i = 0;
            while (i < entities.size()) {
                int index = getIndex(entities[i].bounds);
                if (index != -1) {
                    nodes[index]->insert(entities[i]);
                    entities.erase(entities.begin() + i);
                } else {
                    i++;
                }
            }
        }
    }

    void retrieve(std::vector<Entity>& returnEntities, const AABB& pRect) const {
        int index = getIndex(pRect);
        if (index != -1 && nodes[0] != nullptr) {
            nodes[index]->retrieve(returnEntities, pRect);
        }

        returnEntities.insert(returnEntities.end(), entities.begin(), entities.end());
    }
};
