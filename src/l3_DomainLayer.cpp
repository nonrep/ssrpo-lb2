/* Программа-заготовка для домашнего задания
 */

#include "hw/l3_DomainLayer.h"

using namespace std;

const std::vector<DeviceApp> &Order::getDeviceApps() const
{
    return _device_apps;
}

void Order::setDeviceApps(const std::vector<DeviceApp> &apps) const
{
    _device_apps = apps;
}

std::string Order::getDate() const
{
    return _date;
}

void Order::setDate(const std::string date)
{
    _date = date;
}

const std::vector<Order> &Buyer::getCart() const
{
    return _cart;
}

const std::vector<Order> &Buyer::getOrderHistory() const
{
    return _order_history;
}

void Buyer::setCart(const std::vector<Order> &cart) const
{
    _cart = cart;
}

void Buyer::setOrderHistory(const std::vector<Order> &history) const
{
    _order_history = history;
}

bool DeviceApp::invariant() const
{
    return _app_cost >= MIN_APP_COST && _app_cost <= MAX_APP_COST && _app_size >= MIN_APP_SIZE && _app_size <= MAX_APP_SIZE && _num_of_installing >= MIN_NUM_OF_INSTALLING && _evaluation >= MIN_EVALUATION && _evaluation <= MAX_EVALUATION && !_app_name.empty() && _app_name.size() <= MAX_APP_NAME_LENGTH && !_categoty.empty() && _categoty.size() <= MAX_CATEGORY_LENGTH;
}

DeviceApp::DeviceApp(const std::string &app_name, const std::string &category, uint16_t app_cost, uint16_t app_size, uint32_t num_of_installing, uint8_t evaluation)
    : _app_name(app_name),
      _categoty(category),
      _app_cost(app_cost),
      _app_size(app_size),
      _num_of_installing(num_of_installing),
      _evaluation(evaluation)
{
    assert(invariant());
}

const string &DeviceApp::getAppName() const
{
    return _app_name;
}

const string &DeviceApp::getCategory() const
{
    return _categoty;
}

uint16_t DeviceApp::getAppCost() const
{
    return _app_cost;
}

uint16_t DeviceApp::getAppSize() const
{
    return _app_size;
}

uint32_t DeviceApp::getInstallingNum() const
{
    return _num_of_installing;
}

uint8_t DeviceApp::getEvaluation() const
{
    return _evaluation;
}

bool DeviceApp::write(ostream &os)
{
    writeString(os, _app_name);
    writeString(os, _categoty);
    writeNumber(os, _app_cost);
    writeNumber(os, _app_size);
    writeNumber(os, _num_of_installing);
    writeNumber(os, _evaluation);

    return os.good();
}

shared_ptr<ICollectable> ItemCollector::read(istream &is)
{
    string app_name = readString(is, MAX_APP_NAME_LENGTH);
    string category = readString(is, MAX_CATEGORY_LENGTH);
    uint16_t app_cost = readNumber<uint16_t>(is);
    uint16_t app_size = readNumber<uint16_t>(is);
    uint32_t num_of_installing = readNumber<uint32_t>(is);
    uint8_t evaluation = readNumber<uint8_t>(is);

    return std::make_shared<DeviceApp>(app_name, category, app_cost, app_size, num_of_installing, evaluation);
}

Buyer &ItemCollector::getBuyerRef(size_t index)
{
    Buyer &b = *dynamic_cast<Buyer *>(getItem(index).get());

    return b;
}
