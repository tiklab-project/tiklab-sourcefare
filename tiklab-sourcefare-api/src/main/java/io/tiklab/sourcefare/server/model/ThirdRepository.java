package io.tiklab.sourcefare.server.model;

import io.tiklab.core.BaseModel;

/**
 * 第三方仓库模型
 */
public class ThirdRepository extends BaseModel {

    /**
     * ID
     */
    private String id;

    /**
     * 名称
     */     
    private String name;

    /**
     * 路径
     */
    private String pathWithSpace;

    /**
     * 名称
     */
    private String nameWithSpace;

    /**
     * 仓库web地址
     */
    private String houseWebUrl;

    /**
     * 仓库ssh地址
     */
    private String houseSshUrl;

    /**
     * 默认分支
     */
    private String defaultBranch;

    public String getId() {
        return id;
    }

    public ThirdRepository setId(String id) {
        this.id = id;
        return this;
    }



    public String getName() {
        return name;
    }

    public ThirdRepository setName(String name) {
        this.name = name;
        return this;
    }

    public String getPathWithSpace() {
        return pathWithSpace;
    }

    public ThirdRepository setPathWithSpace(String pathWithSpace) {
        this.pathWithSpace = pathWithSpace;
        return this;
    }

    public String getNameWithSpace() {
        return nameWithSpace;
    }

    public ThirdRepository setNameWithSpace(String nameWithSpace) {
        this.nameWithSpace = nameWithSpace;
        return this;
    }

    public String getHouseWebUrl() {
        return houseWebUrl;
    }

    public ThirdRepository setHouseWebUrl(String houseWebUrl) {
        this.houseWebUrl = houseWebUrl;
        return this;
    }

    public String getHouseSshUrl() {
        return houseSshUrl;
    }

    public ThirdRepository setHouseSshUrl(String houseSshUrl) {
        this.houseSshUrl = houseSshUrl;
        return this;
    }

    public String getDefaultBranch() {
        return defaultBranch;
    }

    public ThirdRepository setDefaultBranch(String defaultBranch) {
        this.defaultBranch = defaultBranch;
        return this;
    }
}
