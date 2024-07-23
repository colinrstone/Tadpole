#ifndef TILEDENTITY_HPP
#define TILEDENTITY_HPP


class TiledEntity 

{
public:


    /** Default constructor.
    *@param x X position (in tiles units).
    *@param y Y position (in tiles units).
    *@param textureAlias Texture alias.
    *@see FilespathProvider::assetPathFromAlias()
    */
    TiledEntity(int x, int y);

    virtual ~TiledEntity();

    void Update();
    void Render();


private:

};

#endif // TILEDENTITY_HPP