if(NOT TARGET OBS::qt-slider-ignorewheel)
  add_subdirectory(
    "${CMAKE_SOURCE_DIR}/shared/qt/slider-ignorewheel"
    "${CMAKE_BINARY_DIR}/shared/qt/slider-ignorewheel"
  )
endif()

target_link_libraries(obs-studio PRIVATE OBS::qt-slider-ignorewheel)

target_sources(
  obs-studio
  PRIVATE
    components/AbsoluteSlider.cpp
    components/AbsoluteSlider.hpp
    components/ApplicationAudioCaptureToolbar.cpp
    components/ApplicationAudioCaptureToolbar.hpp
    components/AudioCaptureToolbar.cpp
    components/AudioCaptureToolbar.hpp
    components/BalanceSlider.hpp
    components/BrowserToolbar.cpp
    components/BrowserToolbar.hpp
    components/ClickableLabel.hpp
    components/ColorSourceToolbar.cpp
    components/ColorSourceToolbar.hpp
    components/ComboSelectToolbar.cpp
    components/ComboSelectToolbar.hpp
    components/DelButton.hpp
    components/DeviceCaptureToolbar.cpp
    components/DeviceCaptureToolbar.hpp
    components/DisplayCaptureToolbar.cpp
    components/DisplayCaptureToolbar.hpp
    components/EditWidget.hpp
    components/FocusList.cpp
    components/FocusList.hpp
    components/GameCaptureToolbar.cpp
    components/GameCaptureToolbar.hpp
    components/HScrollArea.cpp
    components/HScrollArea.hpp
    components/ImageSourceToolbar.cpp
    components/ImageSourceToolbar.hpp
    components/MediaControls.cpp
    components/MediaControls.hpp
    components/MenuButton.cpp
    components/MenuButton.hpp
    components/Multiview.cpp
    components/Multiview.hpp
    components/MuteCheckBox.hpp
    components/NonCheckableButton.hpp
    components/OBSAdvAudioCtrl.cpp
    components/OBSAdvAudioCtrl.hpp
    components/OBSPreviewScalingComboBox.cpp
    components/OBSPreviewScalingComboBox.hpp
    components/OBSPreviewScalingLabel.cpp
    components/OBSPreviewScalingLabel.hpp
    components/OBSSourceLabel.cpp
    components/OBSSourceLabel.hpp
    components/SceneTree.cpp
    components/SceneTree.hpp
    components/SilentUpdateCheckBox.hpp
    components/SilentUpdateSpinBox.hpp
    components/SourceToolbar.cpp
    components/SourceToolbar.hpp
    components/SourceTree.cpp
    components/SourceTree.hpp
    components/SourceTreeDelegate.cpp
    components/SourceTreeDelegate.hpp
    components/SourceTreeItem.cpp
    components/SourceTreeItem.hpp
    components/SourceTreeModel.cpp
    components/SourceTreeModel.hpp
    components/TextSourceToolbar.cpp
    components/TextSourceToolbar.hpp
    components/UIValidation.cpp
    components/UIValidation.hpp
    components/UrlPushButton.cpp
    components/UrlPushButton.hpp
    components/VisibilityItemDelegate.cpp
    components/VisibilityItemDelegate.hpp
    components/VisibilityItemWidget.cpp
    components/VisibilityItemWidget.hpp
    components/VolumeSlider.cpp
    components/VolumeSlider.hpp
    components/WindowCaptureToolbar.cpp
    components/WindowCaptureToolbar.hpp
    components/spt-setting-account-view.cpp
    components/spt-setting-account-view.hpp
    components/spt-complex-header-icon.cpp
    components/spt-complex-header-icon.hpp
    components/SPTFileDownloader.cpp
    components/SPTFileDownloader.hpp
)
