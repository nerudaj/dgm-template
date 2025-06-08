#pragma once

#include <string>
#include <vector>

namespace tiled
{

// docs: https://doc.mapeditor.org/en/stable/reference/json-map-format/

enum class [[nodiscard]] Orientation
{
    Orthogonal,
    Isometric,
    Staggered,
    Hexagonal,
};

NLOHMANN_JSON_SERIALIZE_ENUM(Orientation, {
    { Orientation::Orthogonal, "orthogonal" },
    { Orientation::Isometric, "isometric" },
    { Orientation::Staggered, "staggered" },
    { Orientation::Hexagonal, "hexagonal" },
});

enum class [[nodiscard]] RenderOrder
{
    RightDown,
    RightUp,
    LeftDowm,
    LeftUp,
};

NLOHMANN_JSON_SERIALIZE_ENUM(RenderOrder, {
    { RenderOrder::RightDown, "right-down" },
    { RenderOrder::RightUp, "right-up" },
    { RenderOrder::LeftDown, "left-down" },
    { RenderOrder::LeftUp, "left-up" },
});

enum class [[nodiscard]] LayerType
{
    TileLayer,
};

NLOHMANN_JSON_SERIALIZE_ENUM(LayerType, {
    { LayerType::TileLayer, "tilelayer" },
});

enum class [[nodiscard]] MapType
{
    Map,
};

NLOHMANN_JSON_SERIALIZE_ENUM(MapType, {
    { MapType::Map, "map" },
});

enum class [[nodiscard]] StaggerAxis
{
    X,
    Y,
};

NLOHMANN_JSON_SERIALIZE_ENUM(StaggerAxis, {
    { StaggerAxis::X, "x" },
    { StaggerAxis::Y, "y" },
});

enum class [[nodiscard]] StaggerIndex
{
    Odd,
    Even,
};

NLOHMANN_JSON_SERIALIZE_ENUM(StaggerIndex, {
    { StaggerIndex::Odd, "odd" },
    { StaggerIndex::Even, "even" },
});

struct LayerModel {
    unsigned id = 0;
    std::string name = "";
    std::vector<int> data = {};
    int x = 0;
    int y = 0;
    unsigned width = 0;
    unsigned height = 0;
    unsigned opacity = 0;
    LayerType type = {};
    bool visible = true;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(LayerModel,
    id,
    name,
    data,
    x,
    y,
    width,
    height,
    opacity,
    type,
    visible);

struct TilesetModel
{
    unsigned firstgid = 0;
    std::string source = "";
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TilesetModel,
    firstgid,
    source);

struct FiniteMapModel
{
    int compressionlevel = 0;
    int nextlayerid = 0;
    int nextobjectid = 0;
    unsigned width = 0;
    unsigned height = 0;
    unsigned tilewidth = 0;
    unsigned tileheight = 0;
    std::vector<LayerModel> layers;
    bool infinite = false;
    Orientation orientation = {};
    RenderOrder renderorder = {};
    std::vector<TilesetModel> tilesets = {};
    MapType type = {};
    std::string tiledversion = "";
    std::string version = "";
    double parallaxoriginx = 0.0;
    double parallaxoriginy = 0.0;
    StaggerAxis staggeraxis = {};
    StaggerIndex staggerindex = {};
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(FiniteMapModel,
    compressionlevel,
    nextlayerid,
    nextobjectid,
    width,
    height,
    tilewidth,
    tileheight,
    layers,
    infinite,
    orientation,
    renderorder,
    tilesets,
    type,
    tiledversion,
    version);

}