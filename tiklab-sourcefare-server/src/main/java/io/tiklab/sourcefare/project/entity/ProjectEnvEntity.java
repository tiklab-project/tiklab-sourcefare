package io.tiklab.sourcefare.project.entity;

import io.tiklab.core.BaseModel;
import io.tiklab.dal.jpa.annotation.*;

@Entity
@Table(name="wair_project_env")
public class ProjectEnvEntity extends BaseModel {

    @Id
    @GeneratorValue(length=12)
    @Column(name = "id")
    private String id;

    @Column(name = "project_id")
    private String projectId;


    @Column(name = "env_id")
    private String envId;



    @Column(name = "type")
    private String type;

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getProjectId() {
        return projectId;
    }

    public void setProjectId(String projectId) {
        this.projectId = projectId;
    }

    public String getEnvId() {
        return envId;
    }

    public void setEnvId(String envId) {
        this.envId = envId;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }


}
