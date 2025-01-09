/* Программа-заготовка для домашнего задания
 */

#include "hw/l3_DomainLayer.h"

using namespace std;

Order::Order(const std::string &date, std::vector<DeviceApp> apps)
    : _date(date),
      _device_apps(apps)
{
}

Order::Order(std::vector<DeviceApp> apps)
    : _device_apps(apps)
{
}

const std::vector<DeviceApp> &Order::getDeviceApps() const
{
    return _device_apps;
}

void Order::setDeviceApps(const std::vector<DeviceApp> &apps)
{
    std::lock_guard locker(_orders_mutex);
    _device_apps = apps;
}

void Order::addDeviceApp(const DeviceApp & app)
{
    std::lock_guard locker(_orders_mutex);
    _device_apps.push_back(app);
}

const std::string Order::getDate() const
{
    std::lock_guard locker(_orders_mutex);
    return _date;
}

void Order::setDate(const std::string date)
{
    std::lock_guard locker(_orders_mutex);
    _date = date;
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

bool Order::write(ostream &os)
{
    writeString(os, _date);

    size_t apps_count = _device_apps.size();
    writeNumber(os, apps_count);

    for (const DeviceApp &d : _device_apps)
    {
        writeString(os, d.getAppName());
        writeString(os, d.getCategory());
        writeNumber(os, d.getAppCost());
        writeNumber(os, d.getAppSize());
        writeNumber(os, d.getInstallingNum());
        writeNumber(os, d.getEvaluation());
    }

    return os.good();
}

shared_ptr<ICollectable> ItemCollector::read(istream &is)
{
    string date = readString(is, MAX_DATE_LENGTH);
    size_t apps_count = readNumber<size_t>(is);

    vector<DeviceApp> apps;

    apps.reserve(apps_count);
    for (size_t i = 0; i < apps_count; ++i)
    {
        const string app_name = readString(is, MAX_APP_NAME_LENGTH);
        const string category = readString(is, MAX_CATEGORY_LENGTH);
        uint16_t app_cost = readNumber<uint16_t>(is);
        uint16_t app_size = readNumber<uint16_t>(is);
        uint32_t num_of_installing = readNumber<uint32_t>(is);
        uint8_t evaluation = readNumber<uint8_t>(is);

        apps.push_back(DeviceApp(
            app_name,
            category,
            app_cost,
            app_size,
            num_of_installing,
            evaluation));
    }

    shared_ptr<ICollectable> order = std::make_shared<Order>(date, apps);

    return order;
}

Order &ItemCollector::getOrderRef(size_t index)
{
    Order &b = *static_cast<Order *>(getItem(index).get());

    return b;
}
