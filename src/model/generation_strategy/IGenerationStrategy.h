#pragma once
#include "ErrorHandler.h"
#include "IGenerationConfig.h"
#include "WallMap.h"
#include <functional>
#include <memory>

class IGenerationStrategy
{
    using ErrorCallback = std::function<void(ErrorType)>;
    using RandomFunc = std::function<int(int min, int max)>;

public:
    IGenerationStrategy(ErrorCallback errorCallback = nullptr, RandomFunc randomFunc = nullptr);
    virtual void GenerateMap(const IGenerationConfig &config, const std::shared_ptr<WallMap> &wall_map) = 0;
    bool BaseCheck(const IGenerationConfig &config);
    virtual ~IGenerationStrategy();

protected:
    void emitError(ErrorType error);

private:
    ErrorCallback errorCallback_;

protected:
    RandomFunc randomFunc_;
};
