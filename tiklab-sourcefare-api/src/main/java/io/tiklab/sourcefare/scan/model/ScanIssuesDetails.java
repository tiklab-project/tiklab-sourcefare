package io.tiklab.sourcefare.scan.model;

import io.tiklab.postin.annotation.ApiModel;
import io.tiklab.postin.annotation.ApiProperty;

@ApiModel
public class ScanIssuesDetails {

    @ApiProperty(name="code",desc="代码行")
    private String code;

    @ApiProperty(name="isNew",desc="是否是新")
    private String isNew;

    @ApiProperty(name="line",desc="行")
    private Integer line;

    public String getCode() {
        return code;
    }

    public void setCode(String code) {
        this.code = code;
    }

    public String getIsNew() {
        return isNew;
    }

    public void setIsNew(String isNew) {
        this.isNew = isNew;
    }

    public Integer getLine() {
        return line;
    }

    public void setLine(Integer line) {
        this.line = line;
    }
}
