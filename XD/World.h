#pragma once
#include "GameObject.h"
#include "3DComponents.h"
#include "TexSheet.h"
#include <set>
#include <map>
#include <string>
#include <json_spirit/json_spirit.h>

struct BlockBase;
class Block;
class Chunk;
class World;
class ChunkGenerator;
enum class Material
{
	AIR,
	STONE_BRICKS,
	GLASS,
};

struct id
{
	std::string owner;
	std::string name;

	operator std::string() const;
	operator std::string();
	bool operator<(const id& other) const;

	id(const std::string & name, const std::string& owner) : name(name), owner(owner) {}
	id(const char * name, const char * owner) : name(name), owner(owner) {}
};

struct container
{
public:
	json_spirit::Object data;
	std::set<std::string> properties;
};

class Block : public container
{
private:

	
	glm::uvec3 _posInChunk;
	Chunk * _chunk;

public:

	tex_sheet* texture;

	enum BlockSides {
		UP,
		DOWN,
		SOUTH,
		NORTH,
		EAST,
		WEST
	};

	virtual void onTick() = 0;
	virtual void update() = 0;
	virtual model getModel() = 0;
	virtual id getId() = 0;

	glm::uvec3 getPositionInWorld();
	glm::uvec3 getPositionInChunk();

	Block(Chunk* chunk, const glm::uvec3& posInChunk) : _chunk(chunk), _posInChunk(posInChunk) {}

	virtual ~Block() {}
};

class SolidBlock : public Block
{
public:

	SolidBlock(Chunk* chunk, const glm::uvec3& posInChunk);

	virtual ~SolidBlock() {}
};

class Chunk
{
private:
	Block * _blocks[16][256][16];

	glm::uvec2 _pos;

	World* _world;
public:

	enum ChunkNeighbours {
		NORTH,
		EAST,
		SOUTH,
		WEST
	};
	Chunk * neighbours[4];

	Block* getBlock(const glm::uvec3& posInChunk);
	void setBlock(const glm::uvec3& posInChunk, id blockId);

	glm::uvec2 getPos();

	World* getWorld();

	_declspec (property(get = getPos)) glm::uvec2 position;
	_declspec (property(get = getWorld)) World * world;

	Chunk(World* world, ChunkGenerator* generator, glm::uvec2& pos);
};

class World : public GameObject
{
private:
	struct comparable_uvec2 : glm::uvec2
	{
		bool operator<(const comparable_uvec2& other) const {
			return x != other.x ? x < other.x : y < other.y;
		}

		operator glm::uvec2() { return glm::uvec2(x, y); }

		comparable_uvec2(glm::uvec2 vec) {
			x = vec.x;
			y = vec.y;
		}
	};

	std::map<comparable_uvec2, Chunk*> _activeChunks;
public:
	ChunkGenerator* generator;

	Chunk * getChunk(const glm::uvec2& pos);

	World();
};

class ChunkGenerator
{
public:
	virtual void fillChunk(Chunk* chunk) = 0;
};

class BlankChunkGenerator : public ChunkGenerator
{
public:
	void fillChunk(Chunk* chunk);
};


namespace Core
{
	void registerNewBlock(Block * (*constructor)(Chunk*, const glm::uvec3&));
	void registerNewTextureSheet(id id, tex_sheet* sheet);
	tex_sheet* getTextureSheet(id id);
}