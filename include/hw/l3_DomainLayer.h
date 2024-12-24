/*
MIT License

Copyright (c) 2019 МГТУ им. Н.Э. Баумана, кафедра ИУ-6, Михаил Фетисов,

Программа-заготовка для домашнего задания
*/

#ifndef HW_L3_DOMAIN_LAYER_H
#define HW_L3_DOMAIN_LAYER_H

#include "hw/l4_InfrastructureLayer.h"

const size_t MAX_APP_NAME_LENGTH = 50;
const size_t MAX_CATEGORY_LENGTH = 50;
const size_t MIN_APP_COST = 0;
const size_t MAX_APP_COST = 10000;
const size_t MIN_APP_SIZE = 1;
const size_t MAX_APP_SIZE = 4096;
const size_t MIN_NUM_OF_INSTALLING = 0;
// const size_t MAX_NUM_OF_INSTALLING  = +INF;
const size_t MAX_EVALUATION = 5;
const size_t MIN_EVALUATION = 0;

class Order : public ICollectable
{
    std::string _date;
    std::vector<DeviceApp> &_device_apps;

public:
    const std::vector<DeviceApp> &getDeviceApps() const;
    void setDeviceApps(const std::vector<DeviceApp> &apps) const;
    std::string getDate() const;
    void setDate(const std::string date);
};

class Buyer
{
    std::vector<Order> &_cart;
    std::vector<Order> &_order_history;

public:
    const std::vector<Order> &getCart() const;
    const std::vector<Order> &getOrderHistory() const;
    void setCart(const std::vector<Order> &cart) const;
    void setOrderHistory(const std::vector<Order> &history) const;
};

class DeviceApp : public ICollectable
{
    std::string _app_name;
    std::string _categoty;
    uint16_t _app_cost;
    uint16_t _app_size;
    uint32_t _num_of_installing;
    uint8_t _evaluation;

protected:
    bool invariant() const;

public:
    DeviceApp() = delete;
    DeviceApp(const DeviceApp &p) = delete;

    DeviceApp &operator=(const DeviceApp &p) = delete;

    DeviceApp(const std::string &app_name, const std::string &categoty, uint16_t app_cost, uint16_t app_size, uint32_t num_of_installing, uint8_t evaluation);

    const std::string &getAppName() const;
    const std::string &getCategory() const;
    uint16_t getAppCost() const;
    uint16_t getAppSize() const;
    uint32_t getInstallingNum() const;
    uint8_t getEvaluation() const;

    virtual bool write(std::ostream &os) override;
};

class ItemCollector : public ACollector
{
public:
    virtual std::shared_ptr<ICollectable> read(std::istream &is) override;
    Buyer &ItemCollector::getBuyerRef(size_t index);
};

#endif // HW_L3_DOMAIN_LAYER_H
