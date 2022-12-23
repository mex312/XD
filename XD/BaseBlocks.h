#pragma once
#include "World.h"

class AirBlock : Block
{
public:
	void onTick() {}
	void update() {}
	model getModel() { return model(); }
	id getId() { return id("air", "base"); }

	static Block* getInstance(Chunk* chunk, const glm::uvec3& posInChunk) { return new AirBlock(chunk, posInChunk); }

	AirBlock(Chunk* chunk, const glm::uvec3& posInChunk) : Block(chunk, posInChunk) {}
};






namespace BaseBlocks
{
	void registerAllBlocks() {
		Core::registerNewBlock(AirBlock::getInstance);
	}
}