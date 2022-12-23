#include "World.h"
#include <unordered_map>

typedef glm::vec2 vec2;
typedef glm::vec3 vec3;

std::vector<polygon> blockPolygons = {
	//up
	{
		{vec3(1, 1, 0), vec2(1, 0)},
		{vec3(0, 1, 0), vec2(0, 0)},
		{vec3(0, 1, 1), vec2(0, 1)},
		true
	},{
		{vec3(1, 1, 1), vec2(1, 1)},
		{vec3(1, 1, 0), vec2(1, 0)},
		{vec3(0, 1, 1), vec2(0, 1)},
		true
	},
	//down
	{
		{vec3(0, 0, 0), vec2(0, 1)},
		{vec3(1, 0, 0), vec2(1, 1)},
		{vec3(1, 0, 1), vec2(1, 0)},
		true
	},{
		{vec3(0, 0, 1), vec2(0, 0)},
		{vec3(0, 0, 0), vec2(0, 1)},
		{vec3(1, 0, 1), vec2(1, 0)},
		true
	},
	//front
	{
		{vec3(0, 0, 1), vec2(0, 1)},
		{vec3(1, 1, 1), vec2(1, 0)},
		{vec3(0, 1, 1), vec2(0, 0)},
		true
	},{
		{vec3(1, 0, 1), vec2(1, 1)},
		{vec3(1, 1, 1), vec2(1, 0)},
		{vec3(0, 0, 1), vec2(0, 1)},
		true
	},
	//back
	{
		{vec3(0, 1, 0), vec2(1, 0)},
		{vec3(1, 1, 0), vec2(0, 0)},
		{vec3(0, 0, 0), vec2(1, 1)},
		true
	},{
		{vec3(1, 1, 0), vec2(0, 0)},
		{vec3(1, 0, 0), vec2(0, 1)},
		{vec3(0, 0, 0), vec2(1, 1)},
		true
	},
	//right
	{
		{vec3(1, 1, 0), vec2(1, 0)},
		{vec3(1, 1, 1), vec2(0, 0)},
		{vec3(1, 0, 1), vec2(0, 1)},
		true
	},{
		{vec3(1, 0, 0), vec2(1, 1)},
		{vec3(1, 1, 0), vec2(1, 0)},
		{vec3(1, 0, 1), vec2(0, 1)},
		true
	},
	//left
	{
		{vec3(0, 1, 1), vec2(1, 0)},
		{vec3(0, 1, 0), vec2(0, 0)},
		{vec3(0, 0, 1), vec2(1, 1)},
		true
	},{
		{vec3(0, 1, 0), vec2(0, 0)},
		{vec3(0, 0, 0), vec2(0, 1)},
		{vec3(0, 0, 1), vec2(1, 1)},
		true
	}
};

std::map<id, Block * (*)(Chunk*, const glm::uvec3&)> registeredBlocksConstructors;
std::map<id, tex_sheet*> registeredTextureSheets;

Block* getNewBlock(id blockId, Chunk* chunk, glm::uvec3 pos)
{
	auto found = registeredBlocksConstructors.find(blockId);
	if (found != registeredBlocksConstructors.end())
		return (*found).second(chunk, pos);
	else
		return nullptr;
}

Chunk* World::getChunk(const glm::uvec2& pos)
{
    return _activeChunks[pos];
    //return nullptr;
}

World::World()
{
}

Block* Chunk::getBlock(const glm::uvec3& posInChunk)
{
	return _blocks[posInChunk.x][posInChunk.y][posInChunk.z];
}

void Chunk::setBlock(const glm::uvec3& posInChunk, id blockId)
{
	_blocks[posInChunk.x][posInChunk.y][posInChunk.z] = getNewBlock(blockId, this, posInChunk);
}

glm::uvec2 Chunk::getPos()
{
	return _pos;
}

World* Chunk::getWorld()
{
	return _world;
}

Chunk::Chunk(World* world, ChunkGenerator* generator, glm::uvec2& pos) : _world(world)
{
    neighbours[NORTH] = world->getChunk(pos + glm::uvec2( 0, -1));
    neighbours[EAST]  = world->getChunk(pos + glm::uvec2( 1,  0));
    neighbours[SOUTH] = world->getChunk(pos + glm::uvec2( 0,  1));
    neighbours[WEST]  = world->getChunk(pos + glm::uvec2(-1,  0));

    neighbours[NORTH]->neighbours[SOUTH] = this;
    neighbours[SOUTH]->neighbours[NORTH] = this;
    neighbours[EAST] ->neighbours[WEST]  = this;
    neighbours[WEST] ->neighbours[EAST]  = this;

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 256; j++) {
			for (int l = 0; l < 16; l++) {
				_blocks[i][j][l] =  getNewBlock(id{ "air", "base" }, this, glm::uvec3(i, j, l));
			}
		}
	}

    generator->fillChunk(this);
}

void BlankChunkGenerator::fillChunk(Chunk* chunk)
{
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
			chunk->setBlock(glm::uvec3(i, 0, j), id("glass", "base"));
        }
    }
}

glm::uvec3 Block::getPositionInWorld()
{
	glm::uvec2 xz = _chunk->getPos() * 16u;
	return getPositionInChunk() + glm::uvec3(xz.x, 0, xz.y);
}

glm::uvec3 Block::getPositionInChunk()
{
	return _posInChunk;
}

void Core::registerNewBlock(Block * (*constructor)(Chunk*, const glm::uvec3&))
{
	registeredBlocksConstructors.insert(std::make_pair(constructor(nullptr, glm::uvec3())->getId(), constructor));
}

void Core::registerNewTextureSheet(id id, tex_sheet* sheet)
{
	registeredTextureSheets.insert(std::make_pair(id, sheet));
}

tex_sheet* Core::getTextureSheet(id id)
{
	auto found = registeredTextureSheets.find(id);
	if (found != registeredTextureSheets.end())
		return (*found).second;
	else
		return nullptr;
}

SolidBlock::SolidBlock(Chunk* chunk, const glm::uvec3& posInChunk) : Block(chunk, posInChunk)
{
	_mesh = Mesh(blockPolygons);
}

id::operator std::string()
{
	return owner + ":" + name;
}

id::operator std::string() const
{
	return owner + ":" + name;
}

bool id::operator<(const id& other) const
{
	return (std::string)*this < (std::string)other;
}