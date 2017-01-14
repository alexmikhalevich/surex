#ifndef CSETTINGS_H
#define CSETTINGS_H

class CSettings {
private:
    int m_samples_num;
    int m_max_lod_level;
public:
    CSettings();
    int get_samples_num() const;
    int get_max_lod_level() const;
};

#endif // CSETTINGS_H
