// Phoenix
// Core - A libretro core encapsulated in a C++ object
// Author: athairus
// Created: May 31 2014

#ifndef CORE_H
#define CORE_H

#include <QtCore>
#include <QFile>
#include <QString>
#include <QByteArray>
#include <QImage>
#include <QMap>
#include <QLibrary>

#include "libretro.h"

// Helper for resolving libretro methods
#define resolved_sym( name ) mSymbols->name = ( typeof( mSymbols->name ) )mLibretroCore->resolve( #name );

struct LibretroSymbols {

    LibretroSymbols();
    
    // Libretro core functions
    unsigned( *retro_api_version )( void );
    void ( *retro_cheat_reset )( void );
    void ( *retro_cheat_set )( unsigned , bool , const char * );
    void ( *retro_deinit )( void );
    void *( *retro_get_memory_data )( unsigned );
    size_t ( *retro_get_memory_size )( unsigned );
    unsigned( *retro_get_region )( void );
    void ( *retro_get_system_av_info )( struct retro_system_av_info * );
    void ( *retro_get_system_info )( struct retro_system_info * );
    void ( *retro_init )( void );
    bool ( *retro_load_game )( const struct retro_game_info * );
    bool ( *retro_load_game_special )( unsigned , const struct retro_game_info *, size_t );
    void ( *retro_reset )( void );
    void ( *retro_run )( void );
    bool ( *retro_serialize )( void *, size_t );
    size_t ( *retro_serialize_size )( void );
    void ( *retro_unload_game )( void );
    bool ( *retro_unserialize )( const void *, size_t );
    
    // Frontend-defined callbacks
    void ( *retro_set_audio_sample )( retro_audio_sample_t );
    void ( *retro_set_audio_sample_batch )( retro_audio_sample_batch_t );
    void ( *retro_set_controller_port_device )( unsigned, unsigned );
    void ( *retro_set_environment )( retro_environment_t );
    void ( *retro_set_input_poll )( retro_input_poll_t );
    void ( *retro_set_input_state )( retro_input_state_t );
    void ( *retro_set_video_refresh )( retro_video_refresh_t );
    
    // Optional core-defined callbacks
    void ( *retro_audio )();
    void ( *retro_audio_set_state )( bool enabled );
    void ( *retro_frame_time )( retro_usec_t delta );
    void ( *retro_keyboard_event )( bool down, unsigned keycode, uint32_t character, uint16_t key_modifiers );
    
};

class Core {

public:

    // A pointer to the last instance of the class used
    static Core *core;
    
    Core();
    ~Core();
    
    // Misc
    void doFrame();
    LibretroSymbols *getSymbols();
    QString getLibraryName();
    
    // Video
    const void *getImageData();
    unsigned getMinWidth();
    unsigned getMinHeight();
    unsigned getMaxWidth();
    unsigned getMaxHeight();
    size_t getPitch();
    retro_pixel_format getPixelFormat();
    retro_system_info getSystemInfo();

    // Audio
    int16_t getAudioData();
    size_t getAudioFrames();
    int16_t getLeftChannel();
    int16_t getRightChannel();

    float getAspectRatio();

    // System Timing
    double getFps();
    double getSampleRate();

    // Input

    QMap<unsigned, bool> getKeyBoard();

    // Initilization methods
    bool loadCore( const char * path );
    bool loadGame( const char * path );

    // Unload
    void unload();
    
private:

    // Handle to the libretro core
    QLibrary *mLibretroCore;
    
    // Struct containing libretro methods
    LibretroSymbols *mSymbols;
    
    // Information about the core
    retro_system_av_info *mRetroSystemAVInfo;
    retro_system_info *mRetroSystemInfo;
    // Do something with retro_variable
    retro_input_descriptor mRetroInputDescriptor;
    retro_game_geometry mRetroGameGeometry;
    retro_system_timing mRetroSystemTiming;
    bool mRetroFullpathNeeded;
    
    // Game data
    QByteArray mGameData;
    
    // Video stuff
    unsigned mHeight;
    const void *mImageData;
    size_t mPitch;
    unsigned mWidth;
    retro_pixel_format mPixelFormat;

    // Audio stuff
    size_t audio_frames;
    int16_t audio_data;
    int16_t left_channel;
    int16_t right_channel;

    // Input stuff
    QMap<unsigned, bool> mKeyboard;
    QMap<unsigned, bool> mJoystick;

    // Callbacks
    static void audioSampleCallback( int16_t left, int16_t right );
    static size_t audioSampleBatchCallback( const int16_t *data, size_t frames );
    static bool environmentCallback( unsigned cmd, void *data );
    static void inputPollCallback( void );
    static void logCallback( enum retro_log_level level, const char *fmt, ... );
    static int16_t inputStateCallback( unsigned port, unsigned device, unsigned index, unsigned id );
    static void videoRefreshCallback( const void *data, unsigned width, unsigned height, size_t pitch );
    
};

#endif